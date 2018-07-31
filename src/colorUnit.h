#pragma once
#include "ofxAnimatableFloat.h"
#include "constParameter.h"


//ColorUnit Parameter
const int cColorMax = 255;
const float cColorBreatheLimit = 0.5f;
const float cColorFlashLimit = 0.2f;

enum eColorType
{
	eCT_Off = 0,
	eCT_On,
	eCT_FadeIn,
	eCT_FadeOut,
	eCT_Breathe,
	eCT_Flash,
	eCT_OnAndFadeout
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

		if (_eType == eCT_FadeIn || _eType == eCT_FadeOut || _eType == eCT_Breathe || _eType == eCT_OnAndFadeout)
		{
			_intensity = _animIntensity.getCurrentValue();

			if (_animIntensity.hasFinishedAnimating() && !_isLoop)
			{
				if (_eType == eCT_FadeIn)
				{
					_eType = eCT_On;
				}
				else
				{
					_eType = eCT_Off;
				}
				
			}
		}		
		else if ( _eType == eCT_Flash)
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
		case eCT_On:
		{
			_intensity = MIN(MAX(t, 0), cColorMax);
			break;
		}
		case eCT_FadeIn:
		{
			float breatheT = MAX(cColorBreatheLimit, t);
			//_intensity = 0;
			_animIntensity.reset(0.0f);
			_animIntensity.setDuration(breatheT);
			_animIntensity.setRepeatType(AnimRepeat::PLAY_ONCE);
			_animIntensity.animateFromTo(_intensity, cColorMax);
			_isLoop = false;
			break;
		}
		case eCT_FadeOut:
		{
			float breatheT = MAX(cColorBreatheLimit, t);
			//_intensity = cColorMax;
			_animIntensity.reset(0.0f);
			_animIntensity.setDuration(breatheT);
			_animIntensity.setRepeatType(AnimRepeat::PLAY_ONCE);
			_animIntensity.animateFromTo(_intensity, 0.0);
			_isLoop = false;
			break;
		}
		case eCT_Breathe:
		{
			float breatheT = MAX(cColorBreatheLimit, t);
			_intensity = 0;
			_animIntensity.reset(0.0f);
			_animIntensity.setDuration(breatheT);
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
		case eCT_Flash:
		{
			float flashT = MAX(cColorFlashLimit, t);
			_intensity = 0;
			_timer = _flashTime = flashT;
			break;
		}
		case eCT_OnAndFadeout:
		{
			float breatheT = MAX(cColorBreatheLimit, t);
			_intensity = cColorMax;
			_animIntensity.reset(0.0f);
			_animIntensity.setDuration(breatheT);
			_animIntensity.setRepeatType(AnimRepeat::PLAY_ONCE);
			_animIntensity.animateFromTo(_intensity, 0.0);
			_isLoop = false;
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
