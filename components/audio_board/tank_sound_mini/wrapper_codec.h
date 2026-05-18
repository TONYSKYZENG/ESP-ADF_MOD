/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2019 <ESPRESSIF SYSTEMS (SHANGHAI) CO., LTD>
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

#ifndef _wrapper_codec_H
#define _wrapper_codec_H

#include "audio_hal.h"
#include "esp_types.h"
#include "esxxx_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief Enables or disables PA
 *
 * @param enable     true/false
 *
 * @return
 *      - ESP_ERR_INVALID_ARG
 *      - ESP_OK
 */
esp_err_t wrapper_pa_power(bool enable);

/*
 * @brief Initialize empty codec chip
 *
 * @param codec_cfg  configuration of empty
 *
 * @return
 *      - ESP_OK
 *      - ESP_FAIL
 */
esp_err_t wrapper_codec_init(audio_hal_codec_config_t *codec_cfg);

/**
 * @brief Deinitialize empty codec chip
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t wrapper_codec_deinit(void);

/**
 * @brief Control empty codec chip
 *
 * @param mode codec mode
 * @param ctrl_state start or stop decode or encode progress
 *
 * @return
 *     - ESP_FAIL Parameter error
 *     - ESP_OK   Success
 */
esp_err_t wrapper_codec_ctrl_state(audio_hal_codec_mode_t mode, audio_hal_ctrl_t ctrl_state);

/**
 * @brief Configure empty codec mode and I2S interface
 *
 * @param mode codec mode
 * @param iface I2S config
 *
 * @return
 *     - ESP_FAIL Parameter error
 *     - ESP_OK   Success
 */
esp_err_t wrapper_codec_config_i2s(audio_hal_codec_mode_t mode, audio_hal_codec_i2s_iface_t *iface);

/**
 * @brief Configure empty DAC mute or not. Basically you can use this function to mute the output or unmute
 *
 * @param enable enable(1) or disable(0)
 *
 * @return
 *     - ESP_FAIL Parameter error
 *     - ESP_OK   Success
 */
esp_err_t wrapper_set_voice_mute(bool enable);

/**
 * @brief Set voice volume
 *
 * @param volume:  voice volume (0~100)
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t wrapper_codec_set_voice_volume(int volume);

/**
 * @brief Get voice volume
 *
 * @param[out] *volume:  voice volume (0~100)
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t wrapper_codec_get_voice_volume(int *volume);

/**
 * @brief Configure empty I2S format
 *
 * @param mod:  set ADC or DAC or both
 * @param cfg:   ES8388 I2S format
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t wrapper_config_fmt(es_i2s_fmt_t fmt);

/**
 * @brief Configure empty data sample bits
 *
 * @param mode:  set ADC or DAC or both
 * @param bit_per_sample:  bit number of per sample
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t wrapper_set_bits_per_sample(audio_hal_iface_bits_t bits);

/**
 * @brief  Start empty codec chip
 *
 * @param mode:  set ADC or DAC or both
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t wrapper_start(es_module_t mode);

/**
 * @brief  Stop empty codec chip
 *
 * @param mode:  set ADC or DAC or both
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t wrapper_stop(es_module_t mode);

/**
 * @brief Get empty DAC mute status
 *
 * @return
 *     - ESP_FAIL
 *     - ESP_OK
 */
esp_err_t wrapper_get_voice_mute(int *mute);

/**
 * @brief Set empty mic gain
 *
 * @param gain db of mic gain
 *
 * @return
 *     - ESP_FAIL Parameter error
 *     - ESP_OK   Success
 */
esp_err_t wrapper_set_mic_gain(es_mic_gain_t gain_db);

/**
 * @brief Print all empty registers
 *
 * @return
 *     - void
 */
void wrapper_read_all();

audio_board_handle_t wrapper_audio_board_init(void);

#ifdef __cplusplus
}
#endif

#endif
