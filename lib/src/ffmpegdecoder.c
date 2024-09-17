#include <chiaki/ffmpegdecoder.h>

// Removemos a dependência da biblioteca de vídeo
// #include <libavcodec/avcodec.h>

// Função que mapeava codecs de vídeo removida, pois não precisamos mais identificar codecs
/*
static enum AVCodecID chiaki_codec_av_codec_id(ChiakiCodec codec)
{
	// Sem necessidade de processamento de codec de vídeo
	return AV_CODEC_ID_NONE; // Retorna valor padrão que indica ausência de codec
}
*/

// Função de inicialização do decoder sem vídeo
CHIAKI_EXPORT ChiakiErrorCode chiaki_ffmpeg_decoder_init(ChiakiFfmpegDecoder *decoder, ChiakiLog *log,
		ChiakiCodec codec, const char *hw_decoder_name,
		ChiakiFfmpegFrameAvailable frame_available_cb, void *frame_available_cb_user)
{
	decoder->log = log;
	decoder->frame_available_cb = frame_available_cb;
	decoder->frame_available_cb_user = frame_available_cb_user;

	ChiakiErrorCode err = chiaki_mutex_init(&decoder->mutex, false);
	if(err != CHIAKI_ERR_SUCCESS)
		return err;

	// Como não há mais vídeo, não inicializamos o codec
	decoder->hw_device_ctx = NULL;

	// Sem necessidade de lidar com decodificadores de hardware
	// if(hw_decoder_name) { ... }

	// Inicialização concluída sem vídeo
	return CHIAKI_ERR_SUCCESS;
}

// Função de finalização sem lidar com vídeo
CHIAKI_EXPORT void chiaki_ffmpeg_decoder_fini(ChiakiFfmpegDecoder *decoder)
{
	// Sem recursos de vídeo para liberar, apenas finalizamos o mutex
	chiaki_mutex_fini(&decoder->mutex);
}

// Função de callback de vídeo desativada
CHIAKI_EXPORT bool chiaki_ffmpeg_decoder_video_sample_cb(uint8_t *buf, size_t buf_size, void *user)
{
	// Como não há vídeo, apenas retornamos true sem fazer nada
	return true;
}

// Função que antes puxava frames de vídeo agora não faz nada
CHIAKI_EXPORT AVFrame *chiaki_ffmpeg_decoder_pull_frame(ChiakiFfmpegDecoder *decoder)
{
	// Não há mais frames para puxar
	return NULL;
}

// Função que obtém o formato de pixel foi removida, pois não lidamos com vídeo
/*
CHIAKI_EXPORT enum AVPixelFormat chiaki_ffmpeg_decoder_get_pixel_format(ChiakiFfmpegDecoder *decoder)
{
	// Não há necessidade de formatos de pixel
	return AV_PIX_FMT_NONE;
}
*/
