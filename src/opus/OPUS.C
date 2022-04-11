
static OpusEncoder *enc = NULL;
static int opus_param_frame_size;
static int opus_param_max_packet;


#define VOICE_BITRATE 32000
#define VOICE_PCM_FRAME_DATA_NUM ((VOICE_SAMPLE_RATE/1000)*VOICE_PCM_FRAME_TIME_US/1000) /* 16*20=320 */
#define VOICE_COMPRESSION_RATE (16*VOICE_SAMPLE_RATE/VOICE_BITRATE) /* 256000/32000 = 8 */

#define VOICE_SAMPLE_RATE 16000    

void init_encode_param(void)
{
    /* config OPUS parameters */
    int opus_param_channels;
    int opus_param_application = OPUS_APPLICATION_AUDIO;  
    int opus_param_sampling_rate = VOICE_SAMPLE_RATE;
    int opus_param_bitrate = VOICE_BITRATE;
    int opus_param_bandwidth = OPUS_AUTO;   
    int opus_param_vbr = 0;
    int opus_param_vbr_constraint = 0;
    int opus_param_complexity = 3;
    int opus_param_inband_fec = 0;
    int opus_param_force_channels = OPUS_AUTO;
    int opus_param_dtx = 0;
    int opus_param_packet_loss_perc = 0;
    int opus_param_lsb_depth = 16;
    int opus_param_expert_frame_duration = OPUS_FRAMESIZE_20_MS;
    
	if ((voice_driver_codec_params.codec_ch0_mute == CODEC_CH0_UNMUTE)
				&& (voice_driver_codec_params.codec_ch1_mute == CODEC_CH1_MUTE))
    {
        opus_param_channels = 1;
    }
    else if ((voice_driver_codec_params.codec_ch0_mute == CODEC_CH0_UNMUTE)
             && (voice_driver_codec_params.codec_ch1_mute == CODEC_CH1_UNMUTE))
    {
        opus_param_channels = 2;
    }
    else
    {
        APP_PRINT_ERROR0("[voice_handle_init_encode_param] Invalid codec channels of OPUS!");
        return;
    }

    opus_param_frame_size = VOICE_PCM_FRAME_DATA_NUM;
    opus_param_max_packet = 1500;

    enc = opus_encoder_create(opus_param_sampling_rate, opus_param_channels, opus_param_application,
                              &err);
    if (err == OPUS_OK)
    {
        /* init opus parameters */
        opus_encoder_ctl(enc, OPUS_SET_BITRATE(opus_param_bitrate));
        opus_encoder_ctl(enc, OPUS_SET_BANDWIDTH(opus_param_bandwidth));
        opus_encoder_ctl(enc, OPUS_SET_VBR(opus_param_vbr));
        opus_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(opus_param_vbr_constraint));
        opus_encoder_ctl(enc, OPUS_SET_COMPLEXITY(opus_param_complexity));
        opus_encoder_ctl(enc, OPUS_SET_INBAND_FEC(opus_param_inband_fec));
        opus_encoder_ctl(enc, OPUS_SET_FORCE_CHANNELS(opus_param_force_channels));
        opus_encoder_ctl(enc, OPUS_SET_DTX(opus_param_dtx));
        opus_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(opus_param_packet_loss_perc));
        opus_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(opus_param_lsb_depth));
        opus_encoder_ctl(enc, OPUS_SET_EXPERT_FRAME_DURATION(opus_param_expert_frame_duration));


        /* switch CPU clock to 90MHz, to speed up encoding MPIS */
        if (true == set_system_clock(SYSTEM_90MHZ))
        {
            APP_PRINT_INFO0("[voice_handle_encode_raw_data] set_system_clock to 90MHz");
        }
    }
    else
    {
        APP_PRINT_ERROR0("[voice_handle_init_encode_param] Init OPUS failed!");
    }
	
	
}

void deinit_encode_param(void)
{
        if (enc != NULL)
        {
            opus_encoder_destroy(enc);
        }

        /* swtich CPU clock back to 40MHz, to save power consumption */
        if (true == set_system_clock(SYSTEM_40MHZ))
        {
            APP_PRINT_INFO0("[voice_handle_encode_raw_data] set_system_clock to 40MHz");
        }

}



void encode_raw_data(uint8_t *p_input_data, int32_t input_size,
                                  uint8_t *p_output_data, int32_t *p_output_size)
{

		uint8_t temp_array[4];
    uint32_t enc_final_range;
    int max_payload_bytes = opus_param_max_packet;

    *p_output_size = opus_encode(enc, (opus_int16 *)p_input_data, opus_param_frame_size,
                                 (p_output_data + 8), max_payload_bytes);
    /* add encoder header */
    BE_UINT32_TO_ARRAY(temp_array, *p_output_size);
    memcpy(p_output_data, temp_array, 4);
    opus_encoder_ctl(enc, OPUS_GET_FINAL_RANGE(&enc_final_range));
    BE_UINT32_TO_ARRAY(temp_array, enc_final_range);
    memcpy(p_output_data + 4, temp_array, 4);
    *p_output_size += 8;

}                                  

    