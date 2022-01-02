/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include "Aportaudio.hpp"
#include "opus/opus.h"

#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

namespace Sound
{
    class RecorderPlayer
    {
        public:
            RecorderPlayer();
            ~RecorderPlayer();

            /**
             * have to be call to initialize the audio lib
             * @throw const char *
             */
            void init(void);

            /**
             * have to be call to close the audio lib
             * @throw const char *
             */
            void stop(void);

            /**
             * have to be call in loop
             * @return get a buffer of frame
             * @throw const char *
             */
            std::vector<unsigned short> getMic(void);

            /**
             * @brief decode audio
             * @param decoded encoded audio to decode
             * @return get a buffer of encoded frame
             * @throw const char *
             */
            void frameToSpeaker(const std::vector<unsigned short> &decoded);

            const size_t &getChannelNumber() const;
            const size_t &getSampleRate() const;
            const size_t &getBufferSize() const;

        private:
            Aportaudio audio;

            PaStream *stream;

            size_t channelsNb;
            size_t bufferSize;
            size_t sampleRate;

            PaError err;
    };

    class Codec
    {
        public:
            /**
             * * Create codec to encode and decode audio
             * @param sampleRate frequency of sample
             * @param sampleRate number of channels
             * @param bufferSize buffer size
             * @throw const char *
             */
            Codec(size_t sampleRate, size_t channels, size_t bufferSize);
            ~Codec();

            /**
             * Encode frames
             * @param captured frames get by mic
             * @return encoded frames
             * @throw const char *
             */
            std::vector<unsigned char> encodeFrames(const std::vector<unsigned short> captured);

            /**
             * Decode frames
             * @param encoded frames encoded
             * @return decoded frames
             * @throw const char *
             */
            std::vector<unsigned short> decodeFrames(const std::vector<unsigned char> encoded);

        private:
            size_t bufferSize;
            size_t channels;

            int opusErr;

            opus_int32 enc_bytes;
            opus_int32 dec_bytes;

            OpusEncoder *enc;
            OpusDecoder *dec;
    };

}; // namespace Sound

#endif /* !SOUND_HPP_ */
