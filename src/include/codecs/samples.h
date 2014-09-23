/*
RustyCoder

Copyright (C) 2012-2014 Chak Wai Yuan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CODECS_SAMPLES_H
#define CODECS_SAMPLES_H

class Samples
{
    public:
        Samples() = delete;
        Samples(const Samples &) = delete;
        Samples & operator=(const Samples &) = delete;

        /*!
        Intermediate sample formats.\n
        <b>It can only contain data types which are included in the compiler.</b>
        */
        enum class SampleContainers
        {
            INT_S8,         /*!< char */
            INT_U8,         /*!< unsigned char */
            INT_U8_AS_BYTE, /*!< char. To store samples which cannot fit into any of the other containers as bytes */
            INT_S16,        /*!< short */
            INT_U16,        /*!< unsigned short */
            INT_S32,        /*!< int */
            INT_U32,        /*!< unsigned int */
            FLOAT_32,       /*!< float */
            FLOAT_64        /*!< double */
        };

      //  enum class SampleFormats
      //  {
      //      PCM_INT_S8,
      //      PCM_INT_U8,
      //      PCM_INT_S16,
      //      PCM_INT_U16,
      //      PCM_INT_S24,
      //      PCM_INT_U24,
      //      PCM_INT_S32,
      //      PCM_INT_U32,
      //      PCM_FLOAT_32,
      //      PCM_FLOAT_64,
      //      ULAW,
      //      ALAW,
      //      IMA_ADPCM,
      //      MS_ADPCM,
      //      VOX_ADPCM,
      //      G721_32_ADPCM,
      //      G723_24_ADPCM,
      //      G723_40_ADPCM,
      //      GSM610,
      //      DWVW_12,
      //      DWVW_16,
      //      DWVW_24,
      //      DWVW_N,
      //      DPCM_8,
      //      DPCM_16
      //  };
      //  

      //  /*! This enum must specify container sizes for all sample formats in SampleFormats enum */
      //  enum SuitableSampleContainers
      //  {
      //      PCM_INT_S8_CONTAINER = SampleContainers::INT_S8, /*!< signed 8 bits */
      //      PCM_INT_U8_CONTAINER = SampleContainers::INT_U8, /*!< unsigned 8 bits */
      //      PCM_INT_S16_CONTAINER = SampleContainers::INT_S16, /*!< signed 16 bits */
      //      PCM_INT_U16_CONTAINER = SampleContainers::INT_U16, /*!< unsigned 16 bits */
      //      PCM_INT_S24_CONTAINER = SampleContainers::INT_U8_AS_BYTE, /*!< signed 24 bits. Intentionally use an unsigned 8 bits container because there is no 24 bit container and it is easy to bit shift unsigned 8 bits */
      //      PCM_INT_U24_CONTAINER = SampleContainers::INT_U8_AS_BYTE, /*!< unsigned 24 bits. Same reason as PCM_INT_S24 */
      //      PCM_INT_S32_CONTAINER = SampleContainers::INT_S32, /*!< signed 32 bits */
      //      PCM_INT_U32_CONTAINER = SampleContainers::INT_U32, /*!< unsigned 32 bits */
      //      PCM_FLOAT_32_CONTAINER = SampleContainers::FLOAT_32, /*!< IEEE 754 single precison 32 bits normalized float -1.0 <= x <= 1.0 */
      //      PCM_FLOAT_64_CONTAINER = SampleContainers::FLOAT_64, /*!< IEEE 754 double precison 64 bits normalized float -1.0 <= x <= 1.0 */
      //      ULAW_CONTAINER = SampleContainers::INT_S16, /*!< compress a signed 16 bits sample to 8 bits data */
      //      ALAW_CONTAINER = SampleContainers::INT_S16, /*!< compress a signed 16 bits sample to 8 bits data */
      //      IMA_ADPCM_CONTAINER = SampleContainers::INT_U8_AS_BYTE, /*!< compress a signed 12 bits sample to 4 bits data. Same reason as PCM_INT_S24 */
      //      MS_ADPCM_CONTAINER = SampleContainers::INT_S16, /*!< signed 16 bits */
      //      VOX_ADPCM_CONTAINER = SampleContainers::INT_U8_AS_BYTE, /*!< compress a signed 12 bits sample to 4 bits data. Same reason as PCM_INT_S24 */
            //G721_32_ADPCM_CONTAINER = SampleContainers::INT_S8, /*!< signed 8 bits */
      //      G723_24_ADPCM_CONTAINER = SampleContainers::INT_S8, /*!< signed 8 bits */
      //      G723_40_ADPCM_CONTAINER = SampleContainers::INT_S8, /*!< signed 8 bits */
      //      GSM610_CONTAINER = SampleContainers::INT_S8, /*!< Unknown / Assume signed 8 bits */
      //      DWVW_12_CONTAINER = SampleContainers::INT_U8_AS_BYTE, /*!< Unknown / Assume signed 12 bits. Same reason as PCM_INT_S24 */
      //      DWVW_16_CONTAINER = SampleContainers::INT_S16, /*!< Unknown / Assume signed 16 bits */
      //      DWVW_24_CONTAINER = SampleContainers::INT_U8_AS_BYTE, /*!< Unknown / Assume signed 24 bits. Same reason as PCM_INT_S24 */
      //      DWVW_N_CONTAINER = SampleContainers::INT_U8_AS_BYTE, /*!< Unknown / Assume signed 24 bits. Same reason as PCM_INT_S24 */
      //      DPCM_8_CONTAINER = SampleContainers::INT_S8, /*!< signed 8 bits */
      //      DPCM_16_CONTAINER = SampleContainers::INT_S16 /*!< signed 16 bits */
      //  };
};

#endif