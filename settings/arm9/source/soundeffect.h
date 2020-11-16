#include "common/singleton.h"
#include <maxmod9.h>

#include "soundbank.h"
#include "soundbank_bin.h"

#pragma once
#ifndef _DSIMENUPP_SOUNDEFFECT_H_
#define _DSIMENUPP_SOUNDEFFECT_H_

class SoundEffect
{
  public:
    SoundEffect(): music(false) {
        music = false;
        counter = 0;
    }
    ~SoundEffect() {}

    void init()
    {
        mmInitDefaultMem((mm_addr)soundbank_bin);

        mmLoadEffect(SFX_LAUNCH);
        mmLoadEffect(SFX_SATURNLAUNCH);
        mmLoadEffect(SFX_SELECT);
        mmLoadEffect(SFX_SATURNSELECT);
        mmLoadEffect(SFX_STOP);
        mmLoadEffect(SFX_WRONG);
        mmLoadEffect(SFX_BACK);
        mmLoadEffect(SFX_SATURNBACK);
        mmLoadEffect(SFX_SWITCH);

        snd_launch = {
            {SFX_LAUNCH},            // id
            (int)(1.0f * (1 << 10)), // rate
            0,                       // handle
            255,                     // volume
            128,                     // panning
        };
        snd_saturn_launch = {
            {SFX_SATURNLAUNCH},        // id
            (int)(1.0f * (1 << 10)), // rate
            0,                       // handle
            255,                     // volume
            128,                     // panning
        };
        snd_select = {
            {SFX_SELECT},            // id
            (int)(1.0f * (1 << 10)), // rate
            0,                       // handle
            255,                     // volume
            128,                     // panning
        };
        snd_saturn_select = {
            {SFX_SATURNSELECT},       // id
            (int)(1.0f * (1 << 10)), // rate
            0,                       // handle
            255,                     // volume
            128,                     // panning
        };
        snd_stop = {
            {SFX_STOP},              // id
            (int)(1.0f * (1 << 10)), // rate
            0,                       // handle
            255,                     // volume
            128,                     // panning
        };
        snd_wrong = {
            {SFX_WRONG},             // id
            (int)(1.0f * (1 << 10)), // rate
            0,                       // handle
            255,                     // volume
            128,                     // panning
        };
        snd_back = {
            {SFX_BACK},              // id
            (int)(1.0f * (1 << 10)), // rate
            0,                       // handle
            255,                     // volume
            128,                     // panning
        };
        snd_saturn_back = {
            {SFX_SATURNBACK},         // id
            (int)(1.0f * (1 << 10)), // rate
            0,                       // handle
            255,                     // volume
            128,                     // panning
        };
        snd_switch = {
            {SFX_SWITCH},            // id
            (int)(1.0f * (1 << 10)), // rate
            0,                       // handle
            255,                     // volume
            128,                     // panning
        };
    }

    void playBgMusic()
    {
        if (!music)
        {
			mmLoad(MOD_SETTINGS);
			mmSetModuleVolume(500);
			mmSetModuleTempo(1900);
            music = true;
			mmStart(MOD_SETTINGS, MM_PLAY_LOOP); // Play settings music
        }
    }

    void stopBgMusic()
    {
        if (music) {
			fifoSendValue32(FIFO_USER_01, 1); // Fade out sound
			for (int i = 0; i < 25; i++)
				swiWaitForVBlank();
			mmEffectCancelAll();
			fifoSendValue32(FIFO_USER_01, 0); // Cancel sound fade out
        }
        music = false;
    }

    mm_sound_effect snd_launch;
    mm_sound_effect snd_saturn_launch;
    mm_sound_effect snd_select;
    mm_sound_effect snd_saturn_select;
    mm_sound_effect snd_stop;
    mm_sound_effect snd_wrong;
    mm_sound_effect snd_back;
    mm_sound_effect snd_saturn_back;
    mm_sound_effect snd_switch;

  private:
    bool music;
    int counter;
};

typedef singleton<SoundEffect>
    soundEffect_s;
inline SoundEffect &snd() { return soundEffect_s::instance(); }

#endif
