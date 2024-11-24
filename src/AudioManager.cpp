#include "AudioManager.h"

namespace ThePit {
    namespace AudioManager {
        void load(AUDIO_ASSETS asset_index, const char* filename) {
            THEPIT_ASSERT(asset_index <= MAX_AUDIO_SOURCES);
            wavs[asset_index].load(filename);
        }

        void play(AUDIO_ASSETS asset_index) {
            THEPIT_ASSERT(asset_index <= MAX_AUDIO_SOURCES);
            waves_handles[asset_index] = engine.play(wavs[asset_index]);
        }

        void stop(AUDIO_ASSETS asset_index) {
            THEPIT_ASSERT(asset_index <= MAX_AUDIO_SOURCES);
            engine.stop(waves_handles[asset_index]);
        }
    };
};

