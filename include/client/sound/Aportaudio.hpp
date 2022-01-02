/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Aportaudio
*/

#ifndef APORTAUDIO_HPP_
#define APORTAUDIO_HPP_

#include <portaudio.h>

class Aportaudio {
    public:
        Aportaudio();
        ~Aportaudio();

        PaError Initialize(void);
        PaError Terminate(void);
        PaHostApiIndex GetHostApiCount(void);
        PaHostApiIndex GetDefaultHostApi(void);
        const PaHostApiInfo * GetHostApiInfo(PaHostApiIndex hostApi);
        PaHostApiIndex HostApiTypeIdToHostApiIndex(PaHostApiTypeId type);
        PaDeviceIndex HostApiDeviceIndexToDeviceIndex( PaHostApiIndex hostApi, int hostApiDeviceIndex);
        const PaHostErrorInfo* GetLastHostErrorInfo(void);
        PaDeviceIndex GetDeviceCount(void);
        PaDeviceIndex GetDefaultInputDevice(void);
        PaDeviceIndex GetDefaultOutputDevice(void);
        const PaDeviceInfo* GetDeviceInfo(PaDeviceIndex device);
        PaError IsFormatSupported(const PaStreamParameters *inputParameters, const PaStreamParameters *outputParameters, double sampleRate);
        PaError OpenStream(PaStream** stream, const PaStreamParameters *inputParameters, const PaStreamParameters *outputParameters, double sampleRate, unsigned long framesPerBuffer, PaStreamFlags streamFlags, PaStreamCallback *streamCallback, void *userData);
        PaError OpenDefaultStream(PaStream** stream, int numInputChannels, int numOutputChannels, PaSampleFormat sampleFormat, double sampleRate, unsigned long framesPerBuffer, PaStreamCallback *streamCallback, void *userData);
        PaError CloseStream(PaStream *stream);
        PaError SetStreamFinishedCallback(PaStream *stream, PaStreamFinishedCallback* streamFinishedCallback);
        PaError StartStream(PaStream *stream);
        PaError StopStream(PaStream *stream);
        PaError AbortStream(PaStream *stream);
        PaError IsStreamStopped(PaStream *stream);
        PaError IsStreamActive(PaStream *stream);
        const PaStreamInfo* GetStreamInfo(PaStream *stream);
        PaTime GetStreamTime(PaStream *stream);
        double GetStreamCpuLoad(PaStream* stream);
        PaError ReadStream(PaStream* stream, void *buffer, unsigned long frames);
        PaError WriteStream(PaStream* stream, const void *buffer, unsigned long frames);
        signed long GetStreamReadAvailable(PaStream* stream);
        signed long GetStreamWriteAvailable(PaStream* stream);
        PaError GetSampleSize(PaSampleFormat format);
        void Sleep(long msec);
        const char *GetErrorText(PaError errorCode);

    protected:
    private:
};

#endif /* !APORTAUDIO_HPP_ */
