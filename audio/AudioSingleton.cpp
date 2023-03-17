#include "AudioSingleton.h"


Audio& AudioSingleton::getInstance() {
    static Audio audio;
    return audio;
}

