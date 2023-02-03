/*
    Copyright 2019-2022 Picovoice Inc.

    You may not use this file except in compliance with the license. A copy of the license is located in the "LICENSE"
    file accompanying this source.

    Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
    an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
    specific language governing permissions and limitations under the License.
*/

#ifndef PV_LEOPARD_H
#define PV_LEOPARD_H

#include <stdbool.h>
#include <stdint.h>

#include "picovoice.h"

#ifdef __cplusplus

extern "C" {

#endif

/**
 * Forward Declaration for Leopard speech-to-text engine.
 */
typedef struct pv_leopard pv_leopard_t;

/**
 * Constructor.
 *
 * @param access_key AccessKey obtained from Picovoice Console (https://console.picovoice.ai/)
 * @param model_path Absolute path to the file containing model parameters.
 * @param enable_automatic_punctuation Set to `true` to enable automatic punctuation insertion.
 * @param[out] object Constructed instance of Leopard.
 * @return Status code. Returns `PV_STATUS_OUT_OF_MEMORY`, `PV_STATUS_IO_ERROR`, `PV_STATUS_INVALID_ARGUMENT`,
 * `PV_STATUS_RUNTIME_ERROR`, `PV_STATUS_ACTIVATION_ERROR`, `PV_STATUS_ACTIVATION_LIMIT_REACHED`,
 * `PV_STATUS_ACTIVATION_THROTTLED`, or `PV_STATUS_ACTIVATION_REFUSED` on failure.
 */
PV_API pv_status_t pv_leopard_init(
        const char *access_key,
        const char *model_path,
        bool enable_automatic_punctuation,
        pv_leopard_t **object);

/**
 * Destructor.
 *
 * @param object Leopard object.
 */
PV_API void pv_leopard_delete(pv_leopard_t *object);

/**
 * A transcribed word and its associated metadata.
 */
typedef struct {
    const char *word; /** Transcribed word. */
    float start_sec; /** Start of word in seconds. */
    float end_sec; /** End of word in seconds. */
    float confidence; /** Transcription confidence. It is a number within [0, 1]. */

#ifdef __PV_DUMP__

    int32_t num_phoneme;
    float acoustic_cost;
    float lm_cost;

#endif

} pv_word_t;

/**
 * Processes a given audio data and returns its transcription. The caller is responsible for freeing the transcription
 * buffer.
 *
 * @param object Leopard object.
 * @param pcm Audio data. The audio needs to have a sample rate equal to `pv_sample_rate()` and be 16-bit
 * linearly-encoded. This function operates on single-channel audio.
 * @param num_samples Number of audio samples to process.
 * @param[out] transcript Inferred transcription.
 * @param[out] num_words Number of transcribed words
 * @param[out] words Transcribed words and their associated metadata.
 * @return Status code. Returns `PV_STATUS_OUT_OF_MEMORY`, `PV_STATUS_IO_ERROR`, `PV_STATUS_INVALID_ARGUMENT`,
 * `PV_STATUS_RUNTIME_ERROR`, `PV_STATUS_ACTIVATION_ERROR`, `PV_STATUS_ACTIVATION_LIMIT_REACHED`,
 * `PV_STATUS_ACTIVATION_THROTTLED`, or `PV_STATUS_ACTIVATION_REFUSED` on failure
 */
PV_API pv_status_t pv_leopard_process(
        pv_leopard_t *object,
        const int16_t *pcm,
        int32_t num_samples,
        char **transcript,
        int32_t *num_words,
        pv_word_t **words);

/**
 * Processes a given audio file and returns its transcription. The caller is responsible for freeing the transcription
 * buffer.
 *
 * @param object Leopard object.
 * @param audio_path Absolute path to the audio file. The file needs to have a sample rate equal to or greater than
 * `pv_sample_rate()`. The supported formats are: `3gp (AMR)`, `FLAC`, `MP3`, `MP4/m4a (AAC)`, `Ogg`, `WAV`, `WebM`.
 * Files with stereo audio are mixed into a single mono channel and then processed.
 * @param[out] transcript Inferred transcription.
 * @param[out] num_words Number of transcribed words
 * @param[out] words Transcribed words and their associated metadata.
 * @return Status code. Returns `PV_STATUS_OUT_OF_MEMORY`, `PV_STATUS_IO_ERROR`, `PV_STATUS_INVALID_ARGUMENT`,
 * `PV_STATUS_RUNTIME_ERROR`, `PV_STATUS_ACTIVATION_ERROR`, `PV_STATUS_ACTIVATION_LIMIT_REACHED`,
 * `PV_STATUS_ACTIVATION_THROTTLED`, or `PV_STATUS_ACTIVATION_REFUSED` on failure
 */
PV_API pv_status_t pv_leopard_process_file(
        pv_leopard_t *object,
        const char *audio_path,
        char **transcript,
        int32_t *num_words,
        pv_word_t **words);

/**
 * Getter for version.
 *
 * @return Version.
 */
PV_API const char *pv_leopard_version(void);

#ifdef __cplusplus

}

#endif

#endif // PV_LEOPARD_H
