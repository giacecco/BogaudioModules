
#include <algorithm>

namespace bogaudio {
namespace dsp {

template<typename T>
struct OverlappingBuffer {
	const int _size;
	const int _overlap;
	const int _overlapN;
	const int _samplesN;
	T* _samples;
	int _sample;

	OverlappingBuffer(int size, int o)
	: _size(size)
	, _overlap(o)
	, _overlapN(_size / _overlap)
	, _samplesN(2*_size - _overlapN)
	, _samples(new T[_samplesN])
	, _sample(0)
	{
		assert(_size > 0);
		assert(_overlap > 0 && _overlap <= _size && _size % _overlap == 0);
	}
	virtual ~OverlappingBuffer() {
		delete[] _samples;
	}

	virtual void process(T* samples) = 0;

	virtual bool step(T sample) {
		_samples[_sample++] = sample;
		assert(_sample <= _samplesN);

		if (_sample >= _size && _sample % _overlapN == 0) {
			process(_samples + _sample - _size);

			if (_overlap == 1) {
				_sample = 0;
			}
			else if (_sample == _samplesN) {
				std::copy(_samples + _size, _samples + _samplesN, _samples);
				_sample = _samplesN - _size;
			}

			return true;
		}
		return false;
	}
};


template<typename T>
struct AveragingBuffer {
	const int _size;
	const int _framesN;
	const float _inverseFramesN;
	T* _sums;
	T* _averages;
	T* _frames;
	int _currentFrame;
	const int _resetsPerCommit;
	int _currentReset;

	AveragingBuffer(
		int size,
		int framesToAverage
	)
	: _size(size)
	, _framesN(framesToAverage)
	, _inverseFramesN(1.0 / (float)_framesN)
	, _sums(new T[_size] {})
	, _averages(new T[_size] {})
	, _frames(new T[_size * _framesN] {})
	, _currentFrame(0)
	, _resetsPerCommit(_size / 1000)
	, _currentReset(0)
	{
		assert(framesToAverage > 0);
	}
	~AveragingBuffer() {
		delete[] _sums;
		delete[] _averages;
		delete[] _frames;
	}

	T* getInputFrame() {
		float* frame = _frames + _currentFrame*_size;
		for (int i = 0; i < _size; ++i) {
			_sums[i] -= frame[i];
		}
		return frame;
	}

	void commitInputFrame() {
		float* frame = _frames + _currentFrame*_size;
		for (int i = 0; i < _size; ++i) {
			_sums[i] += frame[i];
			_averages[i] = _sums[i] * _inverseFramesN;
		}

		// Reset the average for some bins, such that reset overhead is even between calls -- avoids buildup of floating point error.
		for (int i = 0; i < _resetsPerCommit; ++i) {
			_sums[_currentReset] = 0.0;
			for (int j = 0; j < _framesN; ++j) {
				_sums[_currentReset] += _frames[j*_size + _currentReset];
			}
			_currentReset = (_currentReset + 1) % _size;
		}

		_currentFrame = (_currentFrame + 1) % _framesN;
	}

	const T* getAverages() {
		return _averages;
	}
};

} // namespace dsp
} // namespace bogaudio
