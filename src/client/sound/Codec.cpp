/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Codec
*/

#include "client/sound/Sound.hpp"

Sound::Codec::Codec(size_t sampleRate, size_t channels, size_t bufferSize)
{
    this->enc = opus_encoder_create(sampleRate, channels, OPUS_APPLICATION_VOIP, &opusErr);
    if (opusErr != OPUS_OK)
        throw (std::string("opus_encoder_create failed: ") + std::to_string(this->opusErr) + std::string("\n")).c_str();

    this->dec = opus_decoder_create(sampleRate, channels, &opusErr);
    if (opusErr != OPUS_OK)
        throw (std::string("opus_decoder_create failed: ") + std::to_string(this->opusErr) + std::string("\n")).c_str();
    this->bufferSize = bufferSize;
    this->channels = channels;
}

Sound::Codec::~Codec()
{
    opus_decoder_destroy(this->dec);
    opus_encoder_destroy(this->enc);
}

std::vector<unsigned char> Sound::Codec::encodeFrames(const std::vector<unsigned short> captured)
{
    std::vector<unsigned char> encoded(this->bufferSize * this->channels * 2);

    if (captured.empty())
        return {};
    if ((this->enc_bytes = opus_encode(this->enc, reinterpret_cast<opus_int16
    const *>(captured.data()), 120, encoded.data(), encoded.size())) < 0) {
        throw (std::string("opus_encode failed: ") + std::to_string(this->enc_bytes) + std::string("\n")).c_str();
    }
    return encoded;
}

std::vector<unsigned short> Sound::Codec::decodeFrames(const std::vector<unsigned char> encode)
{
    std::vector<unsigned short> decoded(this->bufferSize * this->channels);

    if (encode.empty())
        return {};
    if (!encode[0])
        return {};
    // ! ERROR
    if ((this->dec_bytes = opus_decode(this->dec, encode.data(),
                                        this->enc_bytes,
                                        reinterpret_cast<opus_int16 *>(decoded.data()),
                                        120,
                                        0)
                                        )
                                        < 0) {
        throw (std::string("opus_decode failed: ") + std::to_string(this->dec_bytes) + std::string("\n")).c_str();
    }
    return decoded;
}
