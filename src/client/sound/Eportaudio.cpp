/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Aportaudio
*/

#include "client/sound/Aportaudio.hpp"
#include "client/sound/Sound.hpp"

Aportaudio::Aportaudio()
{
}

Aportaudio::~Aportaudio()
{
}

PaError Aportaudio::Initialize(void)
{
    return Pa_Initialize();
}

PaError Aportaudio::Terminate(void)
{
    return Pa_Terminate();
}

PaHostApiIndex Aportaudio::GetHostApiCount(void)
{
    return Pa_GetHostApiCount();
}

PaHostApiIndex Aportaudio::GetDefaultHostApi(void)
{
    return Pa_GetDefaultHostApi();
}

const PaHostApiInfo *Aportaudio::GetHostApiInfo(PaHostApiIndex hostApi)
{
    return Pa_GetHostApiInfo(hostApi);
}

PaHostApiIndex Aportaudio::HostApiTypeIdToHostApiIndex(PaHostApiTypeId type)
{
    return Pa_HostApiTypeIdToHostApiIndex(type);
}

PaDeviceIndex Aportaudio::HostApiDeviceIndexToDeviceIndex(PaHostApiIndex hostApi, int hostApiDeviceIndex)
{
    return Pa_HostApiDeviceIndexToDeviceIndex(hostApi, hostApiDeviceIndex);
}

const PaHostErrorInfo *Aportaudio::GetLastHostErrorInfo(void)
{
    return Pa_GetLastHostErrorInfo();
}

PaDeviceIndex Aportaudio::GetDeviceCount(void)
{
    return Pa_GetDeviceCount();
}

PaDeviceIndex Aportaudio::GetDefaultInputDevice(void)
{
    return Pa_GetDefaultInputDevice();
}

PaDeviceIndex Aportaudio::GetDefaultOutputDevice(void)
{
    return Pa_GetDefaultOutputDevice();
}

const PaDeviceInfo *Aportaudio::GetDeviceInfo(PaDeviceIndex device)
{
    return Pa_GetDeviceInfo(device);
}

PaError Aportaudio::IsFormatSupported(const PaStreamParameters *inputParameters,
                                    const PaStreamParameters *outputParameters,
                                    double sampleRate)
{
    return Pa_IsFormatSupported(inputParameters, outputParameters, sampleRate);
}

PaError Aportaudio::OpenStream(PaStream **stream,
                            const PaStreamParameters *inputParameters,
                            const PaStreamParameters *outputParameters,
                            double sampleRate, unsigned long framesPerBuffer,
                            PaStreamFlags streamFlags,
                            PaStreamCallback *streamCallback,
                            void *userData)
{
    return Pa_OpenStream(stream, inputParameters, outputParameters, sampleRate,
                            framesPerBuffer, streamFlags, streamCallback, userData);
}

PaError Aportaudio::OpenDefaultStream(PaStream** stream, int numInputChannels,
                                int numOutputChannels,
                                PaSampleFormat sampleFormat,
                                double sampleRate,
                                unsigned long framesPerBuffer,
                                PaStreamCallback *streamCallback,
                                void *userData)
{
    return Pa_OpenDefaultStream(stream, numInputChannels, numOutputChannels,
                                sampleFormat, sampleRate, framesPerBuffer,
                                streamCallback, userData);
}

PaError Aportaudio::CloseStream(PaStream *stream)
{
    return Pa_CloseStream(stream);
}

PaError Aportaudio::SetStreamFinishedCallback(PaStream *stream, PaStreamFinishedCallback* streamFinishedCallback)
{
    return Pa_SetStreamFinishedCallback(stream, streamFinishedCallback);
}

PaError Aportaudio::StartStream(PaStream *stream)
{
    return Pa_StartStream(stream);
}

PaError Aportaudio::StopStream(PaStream *stream)
{
    return Pa_StopStream(stream);
}

PaError Aportaudio::AbortStream(PaStream *stream)
{
    return Pa_AbortStream(stream);
}

PaError Aportaudio::IsStreamStopped(PaStream *stream)
{
    return Pa_IsStreamStopped(stream);
}

PaError Aportaudio::IsStreamActive(PaStream *stream)
{
    return Pa_IsStreamActive(stream);
}

const PaStreamInfo *Aportaudio::GetStreamInfo(PaStream *stream)
{
    return Pa_GetStreamInfo(stream);
}

PaTime Aportaudio::GetStreamTime(PaStream *stream)
{
    return Pa_GetStreamTime(stream);
}

double Aportaudio::GetStreamCpuLoad(PaStream *stream)
{
    return Pa_GetStreamCpuLoad(stream);
}

PaError Aportaudio::ReadStream(PaStream *stream, void *buffer, unsigned long frames)
{
    return Pa_ReadStream(stream, buffer, frames);
}

PaError Aportaudio::WriteStream(PaStream *stream, const void *buffer, unsigned long frames)
{
    return Pa_WriteStream(stream, buffer, frames);
}

signed long Aportaudio::GetStreamReadAvailable(PaStream *stream)
{
    return Pa_GetStreamReadAvailable(stream);
}

signed long Aportaudio::GetStreamWriteAvailable(PaStream *stream)
{
    return Pa_GetStreamWriteAvailable(stream);
}

PaError Aportaudio::GetSampleSize(PaSampleFormat format)
{
    return Pa_GetSampleSize(format);
}

void Aportaudio::Sleep(long msec)
{
    return Pa_Sleep(msec);
}

const char *Aportaudio::GetErrorText(PaError errorCode)
{
    return Pa_GetErrorText(errorCode);
}
