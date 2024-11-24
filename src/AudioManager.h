#ifndef THEPIT_AUDIO_MANAGER_H
#define THEPIT_AUDIO_MANAGER_H

#include "Common.h"

#define MAX_AUDIO_SOURCES 32

namespace ThePit {
    enum AUDIO_ASSETS {
        SHOOT,
        MUSIC,
    };
    namespace AudioManager {
        SoLoud::Soloud engine;
        SoLoud::Wav wavs[MAX_AUDIO_SOURCES];
        SoLoud::handle waves_handles[MAX_AUDIO_SOURCES];

        void init_audio_manager() {
            engine.init();
        }
        void deinit_audio_manager() {
            engine.deinit();
        }
        void load(AUDIO_ASSETS asset_index, const char* filename);
        void play(AUDIO_ASSETS asset_index);
        void stop(AUDIO_ASSETS asset_index);
    };
};
#endif