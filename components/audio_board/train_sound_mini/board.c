/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2022 <ESPRESSIF SYSTEMS (SHANGHAI) CO., LTD>
 *
 * Permission is hereby granted for use on all ESPRESSIF SYSTEMS products, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "esp_log.h"
#include "board.h"
#include "audio_mem.h"
#include "periph_sdcard.h"
#include "periph_adc_button.h"
#include "tca9554.h"
/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2022 <ESPRESSIF SYSTEMS (SHANGHAI) CO., LTD>
 *
 * Permission is hereby granted for use on all ESPRESSIF SYSTEMS products, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "esp_log.h"
#include "board.h"
#include "wrapper_codec.h"
static const char *TAG = "AUDIO_BOARD";

static audio_board_handle_t board_handle = 0;
/*
 * operate function of codec
 */
audio_hal_func_t AUDIO_CODEC_wrapper_DEFAULT_HANDLE = {
    .audio_codec_initialize = wrapper_codec_init,
    .audio_codec_deinitialize = wrapper_codec_deinit,
    .audio_codec_ctrl = wrapper_codec_ctrl_state,
    .audio_codec_config_iface = wrapper_codec_config_i2s,
    .audio_codec_set_mute = wrapper_set_voice_mute,
    .audio_codec_set_volume = wrapper_codec_set_voice_volume,
    .audio_codec_get_volume = wrapper_codec_get_voice_volume,
    .audio_codec_enable_pa = wrapper_pa_power,
    .audio_hal_lock = NULL,
    .handle = NULL,
};

audio_board_handle_t audio_board_init(void)
{
    if (board_handle) {
        ESP_LOGW(TAG, "The board has already been initialized!");
        return board_handle;
    }
    board_handle = (audio_board_handle_t) audio_calloc(1, sizeof(struct audio_board_handle));
    AUDIO_MEM_CHECK(TAG, board_handle, return NULL);
    board_handle->audio_hal = audio_board_codec_init();
    return board_handle;
}

audio_hal_handle_t audio_board_codec_init(void)
{
    audio_hal_codec_config_t audio_codec_cfg = AUDIO_CODEC_DEFAULT_CONFIG();
    audio_hal_handle_t codec_hal = audio_hal_init(&audio_codec_cfg, &AUDIO_CODEC_wrapper_DEFAULT_HANDLE);
    AUDIO_NULL_CHECK(TAG, codec_hal, return NULL);
    return codec_hal;
}
esp_err_t audio_board_deinit(audio_board_handle_t audio_board)
{
    esp_err_t ret = ESP_OK;
    ret |= audio_hal_deinit(audio_board->audio_hal);
    audio_free(audio_board);
    board_handle = NULL;
    return ret;
}

esp_err_t wrapper_codec_init(audio_hal_codec_config_t *codec_cfg)
{
    return ESP_OK;
}

esp_err_t wrapper_codec_deinit()
{
    return ESP_OK;
}
esp_err_t wrapper_codec_config_i2s(audio_hal_codec_mode_t mode, audio_hal_codec_i2s_iface_t *iface)
{
    int ret = ESP_OK;
    return ret;
}

esp_err_t wrapper_codec_ctrl_state(audio_hal_codec_mode_t mode, audio_hal_ctrl_t ctrl_state)
{
    esp_err_t ret = ESP_OK;
    return ret;
}
/**
 * @brief Set voice volume
 *
 * @note Register values. 0x00: -95.5 dB, 0x5B: -50 dB, 0xBF: 0 dB, 0xFF: 32 dB
 * @note Accuracy of gain is 0.5 dB
 *
 * @param volume: voice volume (0~100)
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t wrapper_codec_set_voice_volume(int volume)
{
    esp_err_t res = ESP_OK;
    
    return res;
}

esp_err_t wrapper_codec_get_voice_volume(int *volume)
{
    esp_err_t res = ESP_OK;
    int regv = 0;
    regv = 666;
    return res;
}

esp_err_t wrapper_set_voice_mute(bool enable)
{
    //ESP_LOGD(TAG, "emptySetVoiceMute volume:%d", enable);
   // wrapper_mute(enable);
    return ESP_OK;
}

esp_err_t wrapper_get_voice_mute(int *mute)
{
    esp_err_t res = ESP_OK;
    uint8_t reg = 0;
    res = 0;
    return res;
}
esp_err_t wrapper_pa_power(bool enable)
{
    esp_err_t res = ESP_OK;
    return res;
}