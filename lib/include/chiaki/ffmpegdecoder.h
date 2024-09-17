#ifndef CHIAKI_FFMPEG_DECODER_H
#define CHIAKI_FFMPEG_DECODER_H

#include <chiaki/config.h>
#include <chiaki/log.h>
#include <chiaki/thread.h>

#ifdef __cplusplus
extern "C" {
#endif

// Removido o include de libavcodec relacionado ao vídeo
// #include <libavcodec/avcodec.h>

typedef struct chiaki_ffmpeg_decoder_t ChiakiFfmpegDecoder;

// Callback ainda necessário para outros componentes, mesmo sem vídeo
typedef void (*ChiakiFfmpegFrameAvailable)(ChiakiFfmpegDecoder *decoder, void *user);

struct chiaki_ffmpeg_decoder_t
{
	ChiakiLog *log;
	ChiakiMutex mutex;
	// Removido todo o processamento relacionado a vídeo
	// AVCodec *av_codec;
	// AVCodecContext *codec_context;
	// enum AVPixelFormat hw_pix_fmt;
	// AVBufferRef *hw_device_ctx;
	ChiakiMutex cb_mutex;
	ChiakiFfmpegFrameAvailable frame_available_cb;
	void *frame_available_cb_user;
};

// Inicializa o decoder sem vídeo
CHIAKI_EXPORT ChiakiErrorCode chiaki_ffmpeg_decoder_init(ChiakiFfmpegDecoder *decoder, ChiakiLog *log,
		ChiakiCodec codec, const char *hw_decoder_name,
		ChiakiFfmpegFrameAvailable frame_available_cb, void *frame_available_cb_user);

// Finaliza o decoder sem vídeo
CHIAKI_EXPORT void chiaki_ffmpeg_decoder_fini(ChiakiFfmpegDecoder *decoder);

// Callback de vídeo substituída por uma função genérica sem processamento de vídeo
CHIAKI_EXPORT bool chiaki_ffmpeg_decoder_video_sample_cb(uint8_t *buf, size_t buf_size, void *user);

// Função para puxar frames removida, pois não há mais frames de vídeo
// CHIAKI_EXPORT AVFrame *chiaki_ffmpeg_decoder_pull_frame(ChiakiFfmpegDecoder *decoder);

// Função de formato de pixel removida, pois não há mais vídeo
// CHIAKI_EXPORT enum AVPixelFormat chiaki_ffmpeg_decoder_get_pixel_format(ChiakiFfmpegDecoder *decoder);

#ifdef __cplusplus
}
#endif

#endif // CHIAKI_FFMPEG_DECODER_H
