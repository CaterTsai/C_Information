#pragma once
#include "ofxAnimatableFloat.h"
#include "constParameter.h"


//ColorUnit Parameter
const int cColorLow = 75;
const int cColorMiddles = 150;
const int cColorHigh = 255;
const float cColorBreatheSlow = 5.0f;
const float cColorBreatheMiddle = 2.5f;
const float cColorBreatheFast = 0.5f;
const float cColorFlashSlow = 1.0f;
const float cColorFlashFast = 0.2f;

enum eColorType
{
	eCT_Off = 0,
	eCT_OnLow,
	eCT_OnMiddles,
	eCT_OnHigh,

	eCT_BreatheSlow,
	eCT_BreatheMiddle,
	eCT_BreatheFast,
	eCT_BreatheControl,

	eCT_FlashSlow,
	eCT_FlashFast,
	eCT_FlashControl
	
};

class colorUnit {
public:
	colorUnit()
		:_baseColor(255)
		, _intensity(0)
		, _eType(eCT_Off)
		, _isLoop(false)
	{}
	colorUnit(ofColor c)
		:_baseColor(c)
		, _intensity(0)
		, _eType(eCT_Off)
	{}

	void update(float delta)
	{
		_animIntensity.update(delta);

		if (_eType == eCT_BreatheSlow || _eType == eCT_BreatheMiddle || _eType == eCT_BreatheFast)
		{
			_intensity = _animIntensity.getCurrentValue();

			if (_animIntensity.hasFinishedAnimating() && !_isLoop)
			{
				_eType = eCT_Off;
			}
		}		
		else if (_eType == eCT_FlashSlow || _eType == eCT_FlashFast)
		{
			_timer -= delta;
			if (_timer < 0.0f )
			{
				_intensity = (_intensity == 0 ? 255 : 0);
				if (!_isLoop && _intensity == 0)
				{
					_eType = eCT_Off;
				}
				_timer = _flashTime;
			}
		}
	}

	void setColorType(eColorType type, bool isLoop, float t)
	{
		_eType = type;
		_isLoop = isLoop;
		switch (_eType)
		{
		case eCT_Off:
		{
			_intensity = 0;			
			break;
		}
		case eCT_OnLow:
		{
			_intensity = cColorLow;
			break;
		}
		case eCT_OnMiddles:
		{
			_intensity = cColorMiddles;
			break;
		}
		case eCT_OnHigh:
		{
			_intensity = cColorHigh;
			break;
		}
		case eCT_BreatheSlow:
		{
			_intensity = 0;
			_animIntensity.reset(0.0f);
			_animIntensity.setDuration(cColorBreatheSlow);
			if (_isLoop)
			{
				_animIntensity.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH);
			}
			else
			{
				_animIntensity.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH_ONCE);
			}
			
			_animIntensity.animateFromTo(0.0, 255);
			break;
		}
		case eCT_BreatheMiddle:
		{
			_intensity = 0;
			_animIntensity.reset(0.0f);
			_animIntensity.setDuration(cColorBreatheMiddle);
			if (_isLoop)
			{
				_animIntensity.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH);
			}
			else
			{
				_animIntensity.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH_ONCE);
			}
			_animIntensity.animateFromTo(0.0, 255);
			break;
		}
		case eCT_BreatheFast:
		{
			_intensity = 0;
			_animIntensity.reset(0.0f);
			_animIntensity.setDuration(cColorBreatheFast);
			if (_isLoop)
			{
				_animIntensity.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH);
			}
			else
			{
				_animIntensity.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH_ONCE);
			}
			_animIntensity.animateFromTo(0.0, 255);
			break;
		}
		
		case eCT_FlashSlow:
		{
			_intensity = 0;
			_timer = _flashTime = cColorFlashSlow;
			break;
		}
		case eCT_FlashFast:
		{
			_intensity = 0;
			_timer = _flashTime = cColorFlashFast;
			break;
		}
		case eCT_Control:
		{
			break;
		}
		}
	}
	ofColor getDisplayColor()
	{
		ofColor c = _baseColor;
		c.setBrightness(_intensity);
		return c;
	}
	int getIntensity()
	{
		return _intensity;
	}

	void setColor(ofColor c)
	{
		_baseColor = c;
		_intensity = 0;
	}
	void setintensity(int v)
	{
		_intensity = v;
	}


public:
	bool _isLoop;
	eColorType	_eType;
	ofColor _baseColor;
	float _timer, _flashTime;
	int _intensity;
	ofxAnimatableFloat _animIntensity;
};
