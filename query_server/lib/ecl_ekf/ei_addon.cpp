#include "estimator_interface.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/filereadstream.h>
void EstimatorInterface::serializeToJson(rapidjson::Value & ekfObj, rapidjson::Document::AllocatorType & allocator){
	{
		rapidjson::Value structObj(rapidjson::kObjectType);
		structObj.SetObject();
		if (isnan(_params.filter_update_interval_us)){
			structObj.AddMember("filter_update_interval_us", false, allocator);
		}else{
			structObj.AddMember("filter_update_interval_us", _params.filter_update_interval_us, allocator);
		}
		if (isnan(_params.fusion_mode)){
			structObj.AddMember("fusion_mode", false, allocator);
		}else{
			structObj.AddMember("fusion_mode", _params.fusion_mode, allocator);
		}
		if (isnan(_params.vdist_sensor_type)){
			structObj.AddMember("vdist_sensor_type", false, allocator);
		}else{
			structObj.AddMember("vdist_sensor_type", _params.vdist_sensor_type, allocator);
		}
		if (isnan(_params.terrain_fusion_mode)){
			structObj.AddMember("terrain_fusion_mode", false, allocator);
		}else{
			structObj.AddMember("terrain_fusion_mode", _params.terrain_fusion_mode, allocator);
		}
		if (isnan(_params.sensor_interval_max_ms)){
			structObj.AddMember("sensor_interval_max_ms", false, allocator);
		}else{
			structObj.AddMember("sensor_interval_max_ms", _params.sensor_interval_max_ms, allocator);
		}
		if (isnan(_params.mag_delay_ms)){
			structObj.AddMember("mag_delay_ms", false, allocator);
		}else{
			structObj.AddMember("mag_delay_ms", _params.mag_delay_ms, allocator);
		}
		if (isnan(_params.baro_delay_ms)){
			structObj.AddMember("baro_delay_ms", false, allocator);
		}else{
			structObj.AddMember("baro_delay_ms", _params.baro_delay_ms, allocator);
		}
		if (isnan(_params.gps_delay_ms)){
			structObj.AddMember("gps_delay_ms", false, allocator);
		}else{
			structObj.AddMember("gps_delay_ms", _params.gps_delay_ms, allocator);
		}
		if (isnan(_params.airspeed_delay_ms)){
			structObj.AddMember("airspeed_delay_ms", false, allocator);
		}else{
			structObj.AddMember("airspeed_delay_ms", _params.airspeed_delay_ms, allocator);
		}
		if (isnan(_params.flow_delay_ms)){
			structObj.AddMember("flow_delay_ms", false, allocator);
		}else{
			structObj.AddMember("flow_delay_ms", _params.flow_delay_ms, allocator);
		}
		if (isnan(_params.range_delay_ms)){
			structObj.AddMember("range_delay_ms", false, allocator);
		}else{
			structObj.AddMember("range_delay_ms", _params.range_delay_ms, allocator);
		}
		if (isnan(_params.ev_delay_ms)){
			structObj.AddMember("ev_delay_ms", false, allocator);
		}else{
			structObj.AddMember("ev_delay_ms", _params.ev_delay_ms, allocator);
		}
		if (isnan(_params.auxvel_delay_ms)){
			structObj.AddMember("auxvel_delay_ms", false, allocator);
		}else{
			structObj.AddMember("auxvel_delay_ms", _params.auxvel_delay_ms, allocator);
		}
		if (isnan(_params.gyro_noise)){
			structObj.AddMember("gyro_noise", false, allocator);
		}else{
			structObj.AddMember("gyro_noise", _params.gyro_noise, allocator);
		}
		if (isnan(_params.accel_noise)){
			structObj.AddMember("accel_noise", false, allocator);
		}else{
			structObj.AddMember("accel_noise", _params.accel_noise, allocator);
		}
		if (isnan(_params.gyro_bias_p_noise)){
			structObj.AddMember("gyro_bias_p_noise", false, allocator);
		}else{
			structObj.AddMember("gyro_bias_p_noise", _params.gyro_bias_p_noise, allocator);
		}
		if (isnan(_params.accel_bias_p_noise)){
			structObj.AddMember("accel_bias_p_noise", false, allocator);
		}else{
			structObj.AddMember("accel_bias_p_noise", _params.accel_bias_p_noise, allocator);
		}
		if (isnan(_params.mage_p_noise)){
			structObj.AddMember("mage_p_noise", false, allocator);
		}else{
			structObj.AddMember("mage_p_noise", _params.mage_p_noise, allocator);
		}
		if (isnan(_params.magb_p_noise)){
			structObj.AddMember("magb_p_noise", false, allocator);
		}else{
			structObj.AddMember("magb_p_noise", _params.magb_p_noise, allocator);
		}
		if (isnan(_params.wind_vel_p_noise)){
			structObj.AddMember("wind_vel_p_noise", false, allocator);
		}else{
			structObj.AddMember("wind_vel_p_noise", _params.wind_vel_p_noise, allocator);
		}
		if (isnan(_params.terrain_p_noise)){
			structObj.AddMember("terrain_p_noise", false, allocator);
		}else{
			structObj.AddMember("terrain_p_noise", _params.terrain_p_noise, allocator);
		}
		if (isnan(_params.terrain_gradient)){
			structObj.AddMember("terrain_gradient", false, allocator);
		}else{
			structObj.AddMember("terrain_gradient", _params.terrain_gradient, allocator);
		}
		if (isnan(_params.switch_on_gyro_bias)){
			structObj.AddMember("switch_on_gyro_bias", false, allocator);
		}else{
			structObj.AddMember("switch_on_gyro_bias", _params.switch_on_gyro_bias, allocator);
		}
		if (isnan(_params.switch_on_accel_bias)){
			structObj.AddMember("switch_on_accel_bias", false, allocator);
		}else{
			structObj.AddMember("switch_on_accel_bias", _params.switch_on_accel_bias, allocator);
		}
		if (isnan(_params.initial_tilt_err)){
			structObj.AddMember("initial_tilt_err", false, allocator);
		}else{
			structObj.AddMember("initial_tilt_err", _params.initial_tilt_err, allocator);
		}
		if (isnan(_params.gps_vel_noise)){
			structObj.AddMember("gps_vel_noise", false, allocator);
		}else{
			structObj.AddMember("gps_vel_noise", _params.gps_vel_noise, allocator);
		}
		if (isnan(_params.gps_pos_noise)){
			structObj.AddMember("gps_pos_noise", false, allocator);
		}else{
			structObj.AddMember("gps_pos_noise", _params.gps_pos_noise, allocator);
		}
		if (isnan(_params.pos_noaid_noise)){
			structObj.AddMember("pos_noaid_noise", false, allocator);
		}else{
			structObj.AddMember("pos_noaid_noise", _params.pos_noaid_noise, allocator);
		}
		if (isnan(_params.baro_noise)){
			structObj.AddMember("baro_noise", false, allocator);
		}else{
			structObj.AddMember("baro_noise", _params.baro_noise, allocator);
		}
		if (isnan(_params.baro_drift_rate)){
			structObj.AddMember("baro_drift_rate", false, allocator);
		}else{
			structObj.AddMember("baro_drift_rate", _params.baro_drift_rate, allocator);
		}
		if (isnan(_params.baro_innov_gate)){
			structObj.AddMember("baro_innov_gate", false, allocator);
		}else{
			structObj.AddMember("baro_innov_gate", _params.baro_innov_gate, allocator);
		}
		if (isnan(_params.gps_pos_innov_gate)){
			structObj.AddMember("gps_pos_innov_gate", false, allocator);
		}else{
			structObj.AddMember("gps_pos_innov_gate", _params.gps_pos_innov_gate, allocator);
		}
		if (isnan(_params.gps_vel_innov_gate)){
			structObj.AddMember("gps_vel_innov_gate", false, allocator);
		}else{
			structObj.AddMember("gps_vel_innov_gate", _params.gps_vel_innov_gate, allocator);
		}
		if (isnan(_params.gnd_effect_deadzone)){
			structObj.AddMember("gnd_effect_deadzone", false, allocator);
		}else{
			structObj.AddMember("gnd_effect_deadzone", _params.gnd_effect_deadzone, allocator);
		}
		if (isnan(_params.gnd_effect_max_hgt)){
			structObj.AddMember("gnd_effect_max_hgt", false, allocator);
		}else{
			structObj.AddMember("gnd_effect_max_hgt", _params.gnd_effect_max_hgt, allocator);
		}
		if (isnan(_params.mag_heading_noise)){
			structObj.AddMember("mag_heading_noise", false, allocator);
		}else{
			structObj.AddMember("mag_heading_noise", _params.mag_heading_noise, allocator);
		}
		if (isnan(_params.mag_noise)){
			structObj.AddMember("mag_noise", false, allocator);
		}else{
			structObj.AddMember("mag_noise", _params.mag_noise, allocator);
		}
		if (isnan(_params.mag_declination_deg)){
			structObj.AddMember("mag_declination_deg", false, allocator);
		}else{
			structObj.AddMember("mag_declination_deg", _params.mag_declination_deg, allocator);
		}
		if (isnan(_params.heading_innov_gate)){
			structObj.AddMember("heading_innov_gate", false, allocator);
		}else{
			structObj.AddMember("heading_innov_gate", _params.heading_innov_gate, allocator);
		}
		if (isnan(_params.mag_innov_gate)){
			structObj.AddMember("mag_innov_gate", false, allocator);
		}else{
			structObj.AddMember("mag_innov_gate", _params.mag_innov_gate, allocator);
		}
		if (isnan(_params.mag_declination_source)){
			structObj.AddMember("mag_declination_source", false, allocator);
		}else{
			structObj.AddMember("mag_declination_source", _params.mag_declination_source, allocator);
		}
		if (isnan(_params.mag_fusion_type)){
			structObj.AddMember("mag_fusion_type", false, allocator);
		}else{
			structObj.AddMember("mag_fusion_type", _params.mag_fusion_type, allocator);
		}
		if (isnan(_params.mag_acc_gate)){
			structObj.AddMember("mag_acc_gate", false, allocator);
		}else{
			structObj.AddMember("mag_acc_gate", _params.mag_acc_gate, allocator);
		}
		if (isnan(_params.mag_yaw_rate_gate)){
			structObj.AddMember("mag_yaw_rate_gate", false, allocator);
		}else{
			structObj.AddMember("mag_yaw_rate_gate", _params.mag_yaw_rate_gate, allocator);
		}
		if (isnan(_params.gps_heading_noise)){
			structObj.AddMember("gps_heading_noise", false, allocator);
		}else{
			structObj.AddMember("gps_heading_noise", _params.gps_heading_noise, allocator);
		}
		if (isnan(_params.tas_innov_gate)){
			structObj.AddMember("tas_innov_gate", false, allocator);
		}else{
			structObj.AddMember("tas_innov_gate", _params.tas_innov_gate, allocator);
		}
		if (isnan(_params.eas_noise)){
			structObj.AddMember("eas_noise", false, allocator);
		}else{
			structObj.AddMember("eas_noise", _params.eas_noise, allocator);
		}
		if (isnan(_params.arsp_thr)){
			structObj.AddMember("arsp_thr", false, allocator);
		}else{
			structObj.AddMember("arsp_thr", _params.arsp_thr, allocator);
		}
		if (isnan(_params.beta_innov_gate)){
			structObj.AddMember("beta_innov_gate", false, allocator);
		}else{
			structObj.AddMember("beta_innov_gate", _params.beta_innov_gate, allocator);
		}
		if (isnan(_params.beta_noise)){
			structObj.AddMember("beta_noise", false, allocator);
		}else{
			structObj.AddMember("beta_noise", _params.beta_noise, allocator);
		}
		if (isnan(_params.range_noise)){
			structObj.AddMember("range_noise", false, allocator);
		}else{
			structObj.AddMember("range_noise", _params.range_noise, allocator);
		}
		if (isnan(_params.range_innov_gate)){
			structObj.AddMember("range_innov_gate", false, allocator);
		}else{
			structObj.AddMember("range_innov_gate", _params.range_innov_gate, allocator);
		}
		if (isnan(_params.rng_gnd_clearance)){
			structObj.AddMember("rng_gnd_clearance", false, allocator);
		}else{
			structObj.AddMember("rng_gnd_clearance", _params.rng_gnd_clearance, allocator);
		}
		if (isnan(_params.rng_sens_pitch)){
			structObj.AddMember("rng_sens_pitch", false, allocator);
		}else{
			structObj.AddMember("rng_sens_pitch", _params.rng_sens_pitch, allocator);
		}
		if (isnan(_params.range_noise_scaler)){
			structObj.AddMember("range_noise_scaler", false, allocator);
		}else{
			structObj.AddMember("range_noise_scaler", _params.range_noise_scaler, allocator);
		}
		if (isnan(_params.max_hagl_for_range_aid)){
			structObj.AddMember("max_hagl_for_range_aid", false, allocator);
		}else{
			structObj.AddMember("max_hagl_for_range_aid", _params.max_hagl_for_range_aid, allocator);
		}
		if (isnan(_params.max_vel_for_range_aid)){
			structObj.AddMember("max_vel_for_range_aid", false, allocator);
		}else{
			structObj.AddMember("max_vel_for_range_aid", _params.max_vel_for_range_aid, allocator);
		}
		if (isnan(_params.range_aid)){
			structObj.AddMember("range_aid", false, allocator);
		}else{
			structObj.AddMember("range_aid", _params.range_aid, allocator);
		}
		if (isnan(_params.range_aid_innov_gate)){
			structObj.AddMember("range_aid_innov_gate", false, allocator);
		}else{
			structObj.AddMember("range_aid_innov_gate", _params.range_aid_innov_gate, allocator);
		}
		if (isnan(_params.range_valid_quality_s)){
			structObj.AddMember("range_valid_quality_s", false, allocator);
		}else{
			structObj.AddMember("range_valid_quality_s", _params.range_valid_quality_s, allocator);
		}
		if (isnan(_params.range_cos_max_tilt)){
			structObj.AddMember("range_cos_max_tilt", false, allocator);
		}else{
			structObj.AddMember("range_cos_max_tilt", _params.range_cos_max_tilt, allocator);
		}
		if (isnan(_params.range_kin_consistency_gate)){
			structObj.AddMember("range_kin_consistency_gate", false, allocator);
		}else{
			structObj.AddMember("range_kin_consistency_gate", _params.range_kin_consistency_gate, allocator);
		}
		if (isnan(_params.ev_vel_innov_gate)){
			structObj.AddMember("ev_vel_innov_gate", false, allocator);
		}else{
			structObj.AddMember("ev_vel_innov_gate", _params.ev_vel_innov_gate, allocator);
		}
		if (isnan(_params.ev_pos_innov_gate)){
			structObj.AddMember("ev_pos_innov_gate", false, allocator);
		}else{
			structObj.AddMember("ev_pos_innov_gate", _params.ev_pos_innov_gate, allocator);
		}
		if (isnan(_params.flow_noise)){
			structObj.AddMember("flow_noise", false, allocator);
		}else{
			structObj.AddMember("flow_noise", _params.flow_noise, allocator);
		}
		if (isnan(_params.flow_noise_qual_min)){
			structObj.AddMember("flow_noise_qual_min", false, allocator);
		}else{
			structObj.AddMember("flow_noise_qual_min", _params.flow_noise_qual_min, allocator);
		}
		if (isnan(_params.flow_qual_min)){
			structObj.AddMember("flow_qual_min", false, allocator);
		}else{
			structObj.AddMember("flow_qual_min", _params.flow_qual_min, allocator);
		}
		if (isnan(_params.flow_innov_gate)){
			structObj.AddMember("flow_innov_gate", false, allocator);
		}else{
			structObj.AddMember("flow_innov_gate", _params.flow_innov_gate, allocator);
		}
		if (isnan(_params.gps_check_mask)){
			structObj.AddMember("gps_check_mask", false, allocator);
		}else{
			structObj.AddMember("gps_check_mask", _params.gps_check_mask, allocator);
		}
		if (isnan(_params.req_hacc)){
			structObj.AddMember("req_hacc", false, allocator);
		}else{
			structObj.AddMember("req_hacc", _params.req_hacc, allocator);
		}
		if (isnan(_params.req_vacc)){
			structObj.AddMember("req_vacc", false, allocator);
		}else{
			structObj.AddMember("req_vacc", _params.req_vacc, allocator);
		}
		if (isnan(_params.req_sacc)){
			structObj.AddMember("req_sacc", false, allocator);
		}else{
			structObj.AddMember("req_sacc", _params.req_sacc, allocator);
		}
		if (isnan(_params.req_nsats)){
			structObj.AddMember("req_nsats", false, allocator);
		}else{
			structObj.AddMember("req_nsats", _params.req_nsats, allocator);
		}
		if (isnan(_params.req_pdop)){
			structObj.AddMember("req_pdop", false, allocator);
		}else{
			structObj.AddMember("req_pdop", _params.req_pdop, allocator);
		}
		if (isnan(_params.req_hdrift)){
			structObj.AddMember("req_hdrift", false, allocator);
		}else{
			structObj.AddMember("req_hdrift", _params.req_hdrift, allocator);
		}
		if (isnan(_params.req_vdrift)){
			structObj.AddMember("req_vdrift", false, allocator);
		}else{
			structObj.AddMember("req_vdrift", _params.req_vdrift, allocator);
		}
		{
			rapidjson::Value array_params(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_params.PushBack(_params.imu_pos_body(i), allocator);
			}
			structObj.AddMember("imu_pos_body", array_params, allocator);
		}
		{
			rapidjson::Value array_params(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_params.PushBack(_params.gps_pos_body(i), allocator);
			}
			structObj.AddMember("gps_pos_body", array_params, allocator);
		}
		{
			rapidjson::Value array_params(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_params.PushBack(_params.rng_pos_body(i), allocator);
			}
			structObj.AddMember("rng_pos_body", array_params, allocator);
		}
		{
			rapidjson::Value array_params(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_params.PushBack(_params.flow_pos_body(i), allocator);
			}
			structObj.AddMember("flow_pos_body", array_params, allocator);
		}
		{
			rapidjson::Value array_params(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_params.PushBack(_params.ev_pos_body(i), allocator);
			}
			structObj.AddMember("ev_pos_body", array_params, allocator);
		}
		if (isnan(_params.vel_Tau)){
			structObj.AddMember("vel_Tau", false, allocator);
		}else{
			structObj.AddMember("vel_Tau", _params.vel_Tau, allocator);
		}
		if (isnan(_params.pos_Tau)){
			structObj.AddMember("pos_Tau", false, allocator);
		}else{
			structObj.AddMember("pos_Tau", _params.pos_Tau, allocator);
		}
		if (isnan(_params.acc_bias_lim)){
			structObj.AddMember("acc_bias_lim", false, allocator);
		}else{
			structObj.AddMember("acc_bias_lim", _params.acc_bias_lim, allocator);
		}
		if (isnan(_params.acc_bias_learn_acc_lim)){
			structObj.AddMember("acc_bias_learn_acc_lim", false, allocator);
		}else{
			structObj.AddMember("acc_bias_learn_acc_lim", _params.acc_bias_learn_acc_lim, allocator);
		}
		if (isnan(_params.acc_bias_learn_gyr_lim)){
			structObj.AddMember("acc_bias_learn_gyr_lim", false, allocator);
		}else{
			structObj.AddMember("acc_bias_learn_gyr_lim", _params.acc_bias_learn_gyr_lim, allocator);
		}
		if (isnan(_params.acc_bias_learn_tc)){
			structObj.AddMember("acc_bias_learn_tc", false, allocator);
		}else{
			structObj.AddMember("acc_bias_learn_tc", _params.acc_bias_learn_tc, allocator);
		}
		if (isnan(_params.valid_timeout_max)){
			structObj.AddMember("valid_timeout_max", false, allocator);
		}else{
			structObj.AddMember("valid_timeout_max", _params.valid_timeout_max, allocator);
		}
		if (isnan(_params.static_pressure_coef_xp)){
			structObj.AddMember("static_pressure_coef_xp", false, allocator);
		}else{
			structObj.AddMember("static_pressure_coef_xp", _params.static_pressure_coef_xp, allocator);
		}
		if (isnan(_params.static_pressure_coef_xn)){
			structObj.AddMember("static_pressure_coef_xn", false, allocator);
		}else{
			structObj.AddMember("static_pressure_coef_xn", _params.static_pressure_coef_xn, allocator);
		}
		if (isnan(_params.static_pressure_coef_yp)){
			structObj.AddMember("static_pressure_coef_yp", false, allocator);
		}else{
			structObj.AddMember("static_pressure_coef_yp", _params.static_pressure_coef_yp, allocator);
		}
		if (isnan(_params.static_pressure_coef_yn)){
			structObj.AddMember("static_pressure_coef_yn", false, allocator);
		}else{
			structObj.AddMember("static_pressure_coef_yn", _params.static_pressure_coef_yn, allocator);
		}
		if (isnan(_params.static_pressure_coef_z)){
			structObj.AddMember("static_pressure_coef_z", false, allocator);
		}else{
			structObj.AddMember("static_pressure_coef_z", _params.static_pressure_coef_z, allocator);
		}
		if (isnan(_params.max_correction_airspeed)){
			structObj.AddMember("max_correction_airspeed", false, allocator);
		}else{
			structObj.AddMember("max_correction_airspeed", _params.max_correction_airspeed, allocator);
		}
		if (isnan(_params.drag_noise)){
			structObj.AddMember("drag_noise", false, allocator);
		}else{
			structObj.AddMember("drag_noise", _params.drag_noise, allocator);
		}
		if (isnan(_params.bcoef_x)){
			structObj.AddMember("bcoef_x", false, allocator);
		}else{
			structObj.AddMember("bcoef_x", _params.bcoef_x, allocator);
		}
		if (isnan(_params.bcoef_y)){
			structObj.AddMember("bcoef_y", false, allocator);
		}else{
			structObj.AddMember("bcoef_y", _params.bcoef_y, allocator);
		}
		if (isnan(_params.mcoef)){
			structObj.AddMember("mcoef", false, allocator);
		}else{
			structObj.AddMember("mcoef", _params.mcoef, allocator);
		}
		if (isnan(_params.synthesize_mag_z)){
			structObj.AddMember("synthesize_mag_z", false, allocator);
		}else{
			structObj.AddMember("synthesize_mag_z", _params.synthesize_mag_z, allocator);
		}
		if (isnan(_params.check_mag_strength)){
			structObj.AddMember("check_mag_strength", false, allocator);
		}else{
			structObj.AddMember("check_mag_strength", _params.check_mag_strength, allocator);
		}
		if (isnan(_params.EKFGSF_tas_default)){
			structObj.AddMember("EKFGSF_tas_default", false, allocator);
		}else{
			structObj.AddMember("EKFGSF_tas_default", _params.EKFGSF_tas_default, allocator);
		}
		ekfObj.AddMember("_params", structObj, allocator);
	}
{
	if (isnan(_obs_buffer_length)){
		ekfObj.AddMember("_obs_buffer_length", false, allocator);
	}else{
		ekfObj.AddMember("_obs_buffer_length", _obs_buffer_length, allocator);
	}
}
{
	if (isnan(_imu_buffer_length)){
		ekfObj.AddMember("_imu_buffer_length", false, allocator);
	}else{
		ekfObj.AddMember("_imu_buffer_length", _imu_buffer_length, allocator);
	}
}
{
	if (isnan(_dt_imu_avg)){
		ekfObj.AddMember("_dt_imu_avg", false, allocator);
	}else{
		ekfObj.AddMember("_dt_imu_avg", _dt_imu_avg, allocator);
	}
}
{
	if (isnan(_dt_ekf_avg)){
		ekfObj.AddMember("_dt_ekf_avg", false, allocator);
	}else{
		ekfObj.AddMember("_dt_ekf_avg", _dt_ekf_avg, allocator);
	}
}
	{
		rapidjson::Value structObj(rapidjson::kObjectType);
		structObj.SetObject();
		if (isnan(_imu_sample_delayed.time_us)){
			structObj.AddMember("time_us", false, allocator);
		}else{
			structObj.AddMember("time_us", _imu_sample_delayed.time_us, allocator);
		}
		{
			rapidjson::Value array_imu_sample_delayed(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_imu_sample_delayed.PushBack(_imu_sample_delayed.delta_ang(i), allocator);
			}
			structObj.AddMember("delta_ang", array_imu_sample_delayed, allocator);
		}
		{
			rapidjson::Value array_imu_sample_delayed(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_imu_sample_delayed.PushBack(_imu_sample_delayed.delta_vel(i), allocator);
			}
			structObj.AddMember("delta_vel", array_imu_sample_delayed, allocator);
		}
		if (isnan(_imu_sample_delayed.delta_ang_dt)){
			structObj.AddMember("delta_ang_dt", false, allocator);
		}else{
			structObj.AddMember("delta_ang_dt", _imu_sample_delayed.delta_ang_dt, allocator);
		}
		if (isnan(_imu_sample_delayed.delta_vel_dt)){
			structObj.AddMember("delta_vel_dt", false, allocator);
		}else{
			structObj.AddMember("delta_vel_dt", _imu_sample_delayed.delta_vel_dt, allocator);
		}
		{
			rapidjson::Value array_imu_sample_delayed(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_imu_sample_delayed.PushBack(_imu_sample_delayed.delta_vel_clipping[i], allocator);
			}
			structObj.AddMember("delta_vel_clipping", array_imu_sample_delayed, allocator);
		}
		ekfObj.AddMember("_imu_sample_delayed", structObj, allocator);
	}
	{
		rapidjson::Value structObj(rapidjson::kObjectType);
		structObj.SetObject();
		if (isnan(_baro_sample_delayed.time_us)){
			structObj.AddMember("time_us", false, allocator);
		}else{
			structObj.AddMember("time_us", _baro_sample_delayed.time_us, allocator);
		}
		if (isnan(_baro_sample_delayed.hgt)){
			structObj.AddMember("hgt", false, allocator);
		}else{
			structObj.AddMember("hgt", _baro_sample_delayed.hgt, allocator);
		}
		ekfObj.AddMember("_baro_sample_delayed", structObj, allocator);
	}
	{
		rapidjson::Value structObj(rapidjson::kObjectType);
		structObj.SetObject();
		if (isnan(_gps_sample_delayed.time_us)){
			structObj.AddMember("time_us", false, allocator);
		}else{
			structObj.AddMember("time_us", _gps_sample_delayed.time_us, allocator);
		}
		{
			rapidjson::Value array_gps_sample_delayed(rapidjson::kArrayType);
			for(int i = 0; i < 2; i++){
				array_gps_sample_delayed.PushBack(_gps_sample_delayed.pos(i), allocator);
			}
			structObj.AddMember("pos", array_gps_sample_delayed, allocator);
		}
		if (isnan(_gps_sample_delayed.hgt)){
			structObj.AddMember("hgt", false, allocator);
		}else{
			structObj.AddMember("hgt", _gps_sample_delayed.hgt, allocator);
		}
		{
			rapidjson::Value array_gps_sample_delayed(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_gps_sample_delayed.PushBack(_gps_sample_delayed.vel(i), allocator);
			}
			structObj.AddMember("vel", array_gps_sample_delayed, allocator);
		}
		if (isnan(_gps_sample_delayed.yaw)){
			structObj.AddMember("yaw", false, allocator);
		}else{
			structObj.AddMember("yaw", _gps_sample_delayed.yaw, allocator);
		}
		if (isnan(_gps_sample_delayed.hacc)){
			structObj.AddMember("hacc", false, allocator);
		}else{
			structObj.AddMember("hacc", _gps_sample_delayed.hacc, allocator);
		}
		if (isnan(_gps_sample_delayed.vacc)){
			structObj.AddMember("vacc", false, allocator);
		}else{
			structObj.AddMember("vacc", _gps_sample_delayed.vacc, allocator);
		}
		if (isnan(_gps_sample_delayed.sacc)){
			structObj.AddMember("sacc", false, allocator);
		}else{
			structObj.AddMember("sacc", _gps_sample_delayed.sacc, allocator);
		}
		ekfObj.AddMember("_gps_sample_delayed", structObj, allocator);
	}
{
}
	{
		rapidjson::Value structObj(rapidjson::kObjectType);
		structObj.SetObject();
		if (isnan(_airspeed_sample_delayed.time_us)){
			structObj.AddMember("time_us", false, allocator);
		}else{
			structObj.AddMember("time_us", _airspeed_sample_delayed.time_us, allocator);
		}
		if (isnan(_airspeed_sample_delayed.true_airspeed)){
			structObj.AddMember("true_airspeed", false, allocator);
		}else{
			structObj.AddMember("true_airspeed", _airspeed_sample_delayed.true_airspeed, allocator);
		}
		if (isnan(_airspeed_sample_delayed.eas2tas)){
			structObj.AddMember("eas2tas", false, allocator);
		}else{
			structObj.AddMember("eas2tas", _airspeed_sample_delayed.eas2tas, allocator);
		}
		ekfObj.AddMember("_airspeed_sample_delayed", structObj, allocator);
	}
	{
		rapidjson::Value structObj(rapidjson::kObjectType);
		structObj.SetObject();
		if (isnan(_flow_sample_delayed.time_us)){
			structObj.AddMember("time_us", false, allocator);
		}else{
			structObj.AddMember("time_us", _flow_sample_delayed.time_us, allocator);
		}
		{
			rapidjson::Value array_flow_sample_delayed(rapidjson::kArrayType);
			for(int i = 0; i < 2; i++){
				array_flow_sample_delayed.PushBack(_flow_sample_delayed.flow_xy_rad(i), allocator);
			}
			structObj.AddMember("flow_xy_rad", array_flow_sample_delayed, allocator);
		}
		{
			rapidjson::Value array_flow_sample_delayed(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_flow_sample_delayed.PushBack(_flow_sample_delayed.gyro_xyz(i), allocator);
			}
			structObj.AddMember("gyro_xyz", array_flow_sample_delayed, allocator);
		}
		if (isnan(_flow_sample_delayed.dt)){
			structObj.AddMember("dt", false, allocator);
		}else{
			structObj.AddMember("dt", _flow_sample_delayed.dt, allocator);
		}
		if (isnan(_flow_sample_delayed.quality)){
			structObj.AddMember("quality", false, allocator);
		}else{
			structObj.AddMember("quality", _flow_sample_delayed.quality, allocator);
		}
		ekfObj.AddMember("_flow_sample_delayed", structObj, allocator);
	}
	{
		rapidjson::Value structObj(rapidjson::kObjectType);
		structObj.SetObject();
		if (isnan(_ev_sample_delayed.time_us)){
			structObj.AddMember("time_us", false, allocator);
		}else{
			structObj.AddMember("time_us", _ev_sample_delayed.time_us, allocator);
		}
		{
			rapidjson::Value array_ev_sample_delayed(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_ev_sample_delayed.PushBack(_ev_sample_delayed.pos(i), allocator);
			}
			structObj.AddMember("pos", array_ev_sample_delayed, allocator);
		}
		{
			rapidjson::Value array_ev_sample_delayed(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_ev_sample_delayed.PushBack(_ev_sample_delayed.vel(i), allocator);
			}
			structObj.AddMember("vel", array_ev_sample_delayed, allocator);
		}
		{
			rapidjson::Value array_ev_sample_delayed(rapidjson::kArrayType);
			for(int i = 0; i < 4; i++){
				array_ev_sample_delayed.PushBack(_ev_sample_delayed.quat(i), allocator);
			}
			structObj.AddMember("quat", array_ev_sample_delayed, allocator);
		}
		{
			rapidjson::Value array_ev_sample_delayed(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_ev_sample_delayed.PushBack(_ev_sample_delayed.posVar(i), allocator);
			}
			structObj.AddMember("posVar", array_ev_sample_delayed, allocator);
		}
		{
			rapidjson::Value array_ev_sample_delayed(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					array_ev_sample_delayed.PushBack(_ev_sample_delayed.velCov(i, j), allocator);
				}
			}
			structObj.AddMember("velCov", array_ev_sample_delayed, allocator);
		}
		if (isnan(_ev_sample_delayed.angVar)){
			structObj.AddMember("angVar", false, allocator);
		}else{
			structObj.AddMember("angVar", _ev_sample_delayed.angVar, allocator);
		}
		if (isnan(_ev_sample_delayed.reset_counter)){
			structObj.AddMember("reset_counter", false, allocator);
		}else{
			structObj.AddMember("reset_counter", _ev_sample_delayed.reset_counter, allocator);
		}
		ekfObj.AddMember("_ev_sample_delayed", structObj, allocator);
	}
	{
		rapidjson::Value structObj(rapidjson::kObjectType);
		structObj.SetObject();
		if (isnan(_ev_sample_delayed_prev.time_us)){
			structObj.AddMember("time_us", false, allocator);
		}else{
			structObj.AddMember("time_us", _ev_sample_delayed_prev.time_us, allocator);
		}
		{
			rapidjson::Value array_ev_sample_delayed_prev(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_ev_sample_delayed_prev.PushBack(_ev_sample_delayed_prev.pos(i), allocator);
			}
			structObj.AddMember("pos", array_ev_sample_delayed_prev, allocator);
		}
		{
			rapidjson::Value array_ev_sample_delayed_prev(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_ev_sample_delayed_prev.PushBack(_ev_sample_delayed_prev.vel(i), allocator);
			}
			structObj.AddMember("vel", array_ev_sample_delayed_prev, allocator);
		}
		{
			rapidjson::Value array_ev_sample_delayed_prev(rapidjson::kArrayType);
			for(int i = 0; i < 4; i++){
				array_ev_sample_delayed_prev.PushBack(_ev_sample_delayed_prev.quat(i), allocator);
			}
			structObj.AddMember("quat", array_ev_sample_delayed_prev, allocator);
		}
		{
			rapidjson::Value array_ev_sample_delayed_prev(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_ev_sample_delayed_prev.PushBack(_ev_sample_delayed_prev.posVar(i), allocator);
			}
			structObj.AddMember("posVar", array_ev_sample_delayed_prev, allocator);
		}
		{
			rapidjson::Value array_ev_sample_delayed_prev(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					array_ev_sample_delayed_prev.PushBack(_ev_sample_delayed_prev.velCov(i, j), allocator);
				}
			}
			structObj.AddMember("velCov", array_ev_sample_delayed_prev, allocator);
		}
		if (isnan(_ev_sample_delayed_prev.angVar)){
			structObj.AddMember("angVar", false, allocator);
		}else{
			structObj.AddMember("angVar", _ev_sample_delayed_prev.angVar, allocator);
		}
		if (isnan(_ev_sample_delayed_prev.reset_counter)){
			structObj.AddMember("reset_counter", false, allocator);
		}else{
			structObj.AddMember("reset_counter", _ev_sample_delayed_prev.reset_counter, allocator);
		}
		ekfObj.AddMember("_ev_sample_delayed_prev", structObj, allocator);
	}
	{
		rapidjson::Value structObj(rapidjson::kObjectType);
		structObj.SetObject();
		if (isnan(_drag_down_sampled.time_us)){
			structObj.AddMember("time_us", false, allocator);
		}else{
			structObj.AddMember("time_us", _drag_down_sampled.time_us, allocator);
		}
		{
			rapidjson::Value array_drag_down_sampled(rapidjson::kArrayType);
			for(int i = 0; i < 2; i++){
				array_drag_down_sampled.PushBack(_drag_down_sampled.accelXY(i), allocator);
			}
			structObj.AddMember("accelXY", array_drag_down_sampled, allocator);
		}
		ekfObj.AddMember("_drag_down_sampled", structObj, allocator);
	}
{
}
{
	if (isnan(_air_density)){
		ekfObj.AddMember("_air_density", false, allocator);
	}else{
		ekfObj.AddMember("_air_density", _air_density, allocator);
	}
}
{
	if (isnan(_flow_max_rate)){
		ekfObj.AddMember("_flow_max_rate", false, allocator);
	}else{
		ekfObj.AddMember("_flow_max_rate", _flow_max_rate, allocator);
	}
}
{
	if (isnan(_flow_min_distance)){
		ekfObj.AddMember("_flow_min_distance", false, allocator);
	}else{
		ekfObj.AddMember("_flow_min_distance", _flow_min_distance, allocator);
	}
}
{
	if (isnan(_flow_max_distance)){
		ekfObj.AddMember("_flow_max_distance", false, allocator);
	}else{
		ekfObj.AddMember("_flow_max_distance", _flow_max_distance, allocator);
	}
}
	{
		rapidjson::Value structObj(rapidjson::kObjectType);
		structObj.SetObject();
		if (isnan(_output_new.time_us)){
			structObj.AddMember("time_us", false, allocator);
		}else{
			structObj.AddMember("time_us", _output_new.time_us, allocator);
		}
		{
			rapidjson::Value array_output_new(rapidjson::kArrayType);
			for(int i = 0; i < 4; i++){
				array_output_new.PushBack(_output_new.quat_nominal(i), allocator);
			}
			structObj.AddMember("quat_nominal", array_output_new, allocator);
		}
		{
			rapidjson::Value array_output_new(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_output_new.PushBack(_output_new.vel(i), allocator);
			}
			structObj.AddMember("vel", array_output_new, allocator);
		}
		{
			rapidjson::Value array_output_new(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_output_new.PushBack(_output_new.pos(i), allocator);
			}
			structObj.AddMember("pos", array_output_new, allocator);
		}
		ekfObj.AddMember("_output_new", structObj, allocator);
	}
	{
		rapidjson::Value structObj(rapidjson::kObjectType);
		structObj.SetObject();
		if (isnan(_output_vert_new.time_us)){
			structObj.AddMember("time_us", false, allocator);
		}else{
			structObj.AddMember("time_us", _output_vert_new.time_us, allocator);
		}
		if (isnan(_output_vert_new.vert_vel)){
			structObj.AddMember("vert_vel", false, allocator);
		}else{
			structObj.AddMember("vert_vel", _output_vert_new.vert_vel, allocator);
		}
		if (isnan(_output_vert_new.vert_vel_integ)){
			structObj.AddMember("vert_vel_integ", false, allocator);
		}else{
			structObj.AddMember("vert_vel_integ", _output_vert_new.vert_vel_integ, allocator);
		}
		if (isnan(_output_vert_new.dt)){
			structObj.AddMember("dt", false, allocator);
		}else{
			structObj.AddMember("dt", _output_vert_new.dt, allocator);
		}
		ekfObj.AddMember("_output_vert_new", structObj, allocator);
	}
	{
		rapidjson::Value structObj(rapidjson::kObjectType);
		structObj.SetObject();
		if (isnan(_newest_high_rate_imu_sample.time_us)){
			structObj.AddMember("time_us", false, allocator);
		}else{
			structObj.AddMember("time_us", _newest_high_rate_imu_sample.time_us, allocator);
		}
		{
			rapidjson::Value array_newest_high_rate_imu_sample(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_newest_high_rate_imu_sample.PushBack(_newest_high_rate_imu_sample.delta_ang(i), allocator);
			}
			structObj.AddMember("delta_ang", array_newest_high_rate_imu_sample, allocator);
		}
		{
			rapidjson::Value array_newest_high_rate_imu_sample(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_newest_high_rate_imu_sample.PushBack(_newest_high_rate_imu_sample.delta_vel(i), allocator);
			}
			structObj.AddMember("delta_vel", array_newest_high_rate_imu_sample, allocator);
		}
		if (isnan(_newest_high_rate_imu_sample.delta_ang_dt)){
			structObj.AddMember("delta_ang_dt", false, allocator);
		}else{
			structObj.AddMember("delta_ang_dt", _newest_high_rate_imu_sample.delta_ang_dt, allocator);
		}
		if (isnan(_newest_high_rate_imu_sample.delta_vel_dt)){
			structObj.AddMember("delta_vel_dt", false, allocator);
		}else{
			structObj.AddMember("delta_vel_dt", _newest_high_rate_imu_sample.delta_vel_dt, allocator);
		}
		{
			rapidjson::Value array_newest_high_rate_imu_sample(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_newest_high_rate_imu_sample.PushBack(_newest_high_rate_imu_sample.delta_vel_clipping[i], allocator);
			}
			structObj.AddMember("delta_vel_clipping", array_newest_high_rate_imu_sample, allocator);
		}
		ekfObj.AddMember("_newest_high_rate_imu_sample", structObj, allocator);
	}
{
	{
		rapidjson::Value array_R_to_earth_now(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				array_R_to_earth_now.PushBack(_R_to_earth_now(i, j), allocator);
			}
		}
		ekfObj.AddMember("_R_to_earth_now", array_R_to_earth_now, allocator);
	}
}
{
	{
		rapidjson::Value array_vel_imu_rel_body_ned(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_vel_imu_rel_body_ned.PushBack(_vel_imu_rel_body_ned(i), allocator);
		}
		ekfObj.AddMember("_vel_imu_rel_body_ned", array_vel_imu_rel_body_ned, allocator);
	}
}
{
	{
		rapidjson::Value array_vel_deriv(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_vel_deriv.PushBack(_vel_deriv(i), allocator);
		}
		ekfObj.AddMember("_vel_deriv", array_vel_deriv, allocator);
	}
}
{
	if (isnan(_imu_updated)){
		ekfObj.AddMember("_imu_updated", false, allocator);
	}else{
		ekfObj.AddMember("_imu_updated", _imu_updated, allocator);
	}
}
{
	if (isnan(_initialised)){
		ekfObj.AddMember("_initialised", false, allocator);
	}else{
		ekfObj.AddMember("_initialised", _initialised, allocator);
	}
}
{
	if (isnan(_NED_origin_initialised)){
		ekfObj.AddMember("_NED_origin_initialised", false, allocator);
	}else{
		ekfObj.AddMember("_NED_origin_initialised", _NED_origin_initialised, allocator);
	}
}
{
	if (isnan(_gps_speed_valid)){
		ekfObj.AddMember("_gps_speed_valid", false, allocator);
	}else{
		ekfObj.AddMember("_gps_speed_valid", _gps_speed_valid, allocator);
	}
}
{
	if (isnan(_gps_origin_eph)){
		ekfObj.AddMember("_gps_origin_eph", false, allocator);
	}else{
		ekfObj.AddMember("_gps_origin_eph", _gps_origin_eph, allocator);
	}
}
{
	if (isnan(_gps_origin_epv)){
		ekfObj.AddMember("_gps_origin_epv", false, allocator);
	}else{
		ekfObj.AddMember("_gps_origin_epv", _gps_origin_epv, allocator);
	}
}
	{
		rapidjson::Value structObj(rapidjson::kObjectType);
		structObj.SetObject();
{uint64_t a; double b,c,d,e; bool f; _pos_ref.get(a, b, c, d, e, f); structObj.AddMember("_ref_timestamp", a, allocator);structObj.AddMember("_ref_lat", b, allocator);structObj.AddMember("_ref_lon", c, allocator);structObj.AddMember("_ref_sin_lat", d, allocator);structObj.AddMember("_ref_cos_lat", e, allocator);structObj.AddMember("_ref_init_done", f, allocator);}
		ekfObj.AddMember("_pos_ref", structObj, allocator);
	}
	{
		rapidjson::Value structObj(rapidjson::kObjectType);
		structObj.SetObject();
{uint64_t a; double b,c,d,e; bool f; _gps_pos_prev.get(a, b, c, d, e, f); structObj.AddMember("_ref_timestamp", a, allocator);structObj.AddMember("_ref_lat", b, allocator);structObj.AddMember("_ref_lon", c, allocator);structObj.AddMember("_ref_sin_lat", d, allocator);structObj.AddMember("_ref_cos_lat", e, allocator);structObj.AddMember("_ref_init_done", f, allocator);}
		ekfObj.AddMember("_gps_pos_prev", structObj, allocator);
	}
{
	if (isnan(_gps_alt_prev)){
		ekfObj.AddMember("_gps_alt_prev", false, allocator);
	}else{
		ekfObj.AddMember("_gps_alt_prev", _gps_alt_prev, allocator);
	}
}
{
	if (isnan(_gps_yaw_offset)){
		ekfObj.AddMember("_gps_yaw_offset", false, allocator);
	}else{
		ekfObj.AddMember("_gps_yaw_offset", _gps_yaw_offset, allocator);
	}
}
{
	if (isnan(_yaw_test_ratio)){
		ekfObj.AddMember("_yaw_test_ratio", false, allocator);
	}else{
		ekfObj.AddMember("_yaw_test_ratio", _yaw_test_ratio, allocator);
	}
}
	{
		rapidjson::Value floatAF(rapidjson::kObjectType);
		floatAF.AddMember("_cutoff_freq", _yaw_signed_test_ratio_lpf.getCutoffFreq(), allocator);
		floatAF.AddMember("_alpha", _yaw_signed_test_ratio_lpf.getAlpha(), allocator);
		if (isnan(_yaw_signed_test_ratio_lpf.getState())){
			floatAF.AddMember("_filter_state", false, allocator);
		}else{
			floatAF.AddMember("_filter_state", _yaw_signed_test_ratio_lpf.getState(), allocator);
		}
		ekfObj.AddMember("_yaw_signed_test_ratio_lpf", floatAF, allocator);
	}
{
	{
		rapidjson::Value array_mag_test_ratio(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_mag_test_ratio.PushBack(_mag_test_ratio(i), allocator);
		}
		ekfObj.AddMember("_mag_test_ratio", array_mag_test_ratio, allocator);
	}
}
{
	{
		rapidjson::Value array_gps_vel_test_ratio(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_gps_vel_test_ratio.PushBack(_gps_vel_test_ratio(i), allocator);
		}
		ekfObj.AddMember("_gps_vel_test_ratio", array_gps_vel_test_ratio, allocator);
	}
}
{
	{
		rapidjson::Value array_gps_pos_test_ratio(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_gps_pos_test_ratio.PushBack(_gps_pos_test_ratio(i), allocator);
		}
		ekfObj.AddMember("_gps_pos_test_ratio", array_gps_pos_test_ratio, allocator);
	}
}
{
	{
		rapidjson::Value array_ev_vel_test_ratio(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_ev_vel_test_ratio.PushBack(_ev_vel_test_ratio(i), allocator);
		}
		ekfObj.AddMember("_ev_vel_test_ratio", array_ev_vel_test_ratio, allocator);
	}
}
{
	{
		rapidjson::Value array_ev_pos_test_ratio(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_ev_pos_test_ratio.PushBack(_ev_pos_test_ratio(i), allocator);
		}
		ekfObj.AddMember("_ev_pos_test_ratio", array_ev_pos_test_ratio, allocator);
	}
}
{
	{
		rapidjson::Value array_aux_vel_test_ratio(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_aux_vel_test_ratio.PushBack(_aux_vel_test_ratio(i), allocator);
		}
		ekfObj.AddMember("_aux_vel_test_ratio", array_aux_vel_test_ratio, allocator);
	}
}
{
	if (isnan(_baro_hgt_test_ratio)){
		ekfObj.AddMember("_baro_hgt_test_ratio", false, allocator);
	}else{
		ekfObj.AddMember("_baro_hgt_test_ratio", _baro_hgt_test_ratio, allocator);
	}
}
{
	if (isnan(_rng_hgt_test_ratio)){
		ekfObj.AddMember("_rng_hgt_test_ratio", false, allocator);
	}else{
		ekfObj.AddMember("_rng_hgt_test_ratio", _rng_hgt_test_ratio, allocator);
	}
}
{
	if (isnan(_optflow_test_ratio)){
		ekfObj.AddMember("_optflow_test_ratio", false, allocator);
	}else{
		ekfObj.AddMember("_optflow_test_ratio", _optflow_test_ratio, allocator);
	}
}
{
	if (isnan(_tas_test_ratio)){
		ekfObj.AddMember("_tas_test_ratio", false, allocator);
	}else{
		ekfObj.AddMember("_tas_test_ratio", _tas_test_ratio, allocator);
	}
}
{
	if (isnan(_hagl_test_ratio)){
		ekfObj.AddMember("_hagl_test_ratio", false, allocator);
	}else{
		ekfObj.AddMember("_hagl_test_ratio", _hagl_test_ratio, allocator);
	}
}
{
	if (isnan(_beta_test_ratio)){
		ekfObj.AddMember("_beta_test_ratio", false, allocator);
	}else{
		ekfObj.AddMember("_beta_test_ratio", _beta_test_ratio, allocator);
	}
}
{
	{
		rapidjson::Value array_drag_test_ratio(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_drag_test_ratio.PushBack(_drag_test_ratio(i), allocator);
		}
		ekfObj.AddMember("_drag_test_ratio", array_drag_test_ratio, allocator);
	}
}
	{
		rapidjson::Value unionJson(rapidjson::kObjectType);
		rapidjson::Value innerJson(rapidjson::kObjectType);
		innerJson.AddMember("reject_airspeed", _innov_check_fail_status.flags.reject_airspeed, allocator);
		innerJson.AddMember("reject_hagl", _innov_check_fail_status.flags.reject_hagl, allocator);
		innerJson.AddMember("reject_hor_pos", _innov_check_fail_status.flags.reject_hor_pos, allocator);
		innerJson.AddMember("reject_hor_vel", _innov_check_fail_status.flags.reject_hor_vel, allocator);
		innerJson.AddMember("reject_mag_x", _innov_check_fail_status.flags.reject_mag_x, allocator);
		innerJson.AddMember("reject_mag_y", _innov_check_fail_status.flags.reject_mag_y, allocator);
		innerJson.AddMember("reject_mag_z", _innov_check_fail_status.flags.reject_mag_z, allocator);
		innerJson.AddMember("reject_optflow_X", _innov_check_fail_status.flags.reject_optflow_X, allocator);
		innerJson.AddMember("reject_optflow_Y", _innov_check_fail_status.flags.reject_optflow_Y, allocator);
		innerJson.AddMember("reject_sideslip", _innov_check_fail_status.flags.reject_sideslip, allocator);
		innerJson.AddMember("reject_ver_pos", _innov_check_fail_status.flags.reject_ver_pos, allocator);
		innerJson.AddMember("reject_ver_vel", _innov_check_fail_status.flags.reject_ver_vel, allocator);
		innerJson.AddMember("reject_yaw", _innov_check_fail_status.flags.reject_yaw, allocator);
		unionJson.AddMember("flags", innerJson, allocator);
		ekfObj.AddMember("_innov_check_fail_status", unionJson, allocator);
	}{
	if (isnan(_deadreckon_time_exceeded)){
		ekfObj.AddMember("_deadreckon_time_exceeded", false, allocator);
	}else{
		ekfObj.AddMember("_deadreckon_time_exceeded", _deadreckon_time_exceeded, allocator);
	}
}
{
	if (isnan(_gps_horizontal_position_drift_rate_m_s)){
		ekfObj.AddMember("_gps_horizontal_position_drift_rate_m_s", false, allocator);
	}else{
		ekfObj.AddMember("_gps_horizontal_position_drift_rate_m_s", _gps_horizontal_position_drift_rate_m_s, allocator);
	}
}
{
	if (isnan(_gps_vertical_position_drift_rate_m_s)){
		ekfObj.AddMember("_gps_vertical_position_drift_rate_m_s", false, allocator);
	}else{
		ekfObj.AddMember("_gps_vertical_position_drift_rate_m_s", _gps_vertical_position_drift_rate_m_s, allocator);
	}
}
{
	if (isnan(_gps_filtered_horizontal_velocity_m_s)){
		ekfObj.AddMember("_gps_filtered_horizontal_velocity_m_s", false, allocator);
	}else{
		ekfObj.AddMember("_gps_filtered_horizontal_velocity_m_s", _gps_filtered_horizontal_velocity_m_s, allocator);
	}
}
{
	if (isnan(_time_last_on_ground_us)){
		ekfObj.AddMember("_time_last_on_ground_us", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_on_ground_us", _time_last_on_ground_us, allocator);
	}
}
{
	if (isnan(_time_last_in_air)){
		ekfObj.AddMember("_time_last_in_air", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_in_air", _time_last_in_air, allocator);
	}
}
	{
		rapidjson::Value imuSample_buffer(rapidjson::kObjectType);
		imuSample_buffer.AddMember("_head", _imu_buffer.get_head(), allocator);
		imuSample_buffer.AddMember("_tail", _imu_buffer.get_tail(), allocator);
		imuSample_buffer.AddMember("_size", _imu_buffer.get_length(), allocator);
		imuSample_buffer.AddMember("_first_write", _imu_buffer.get_first_write(), allocator);
		rapidjson::Value buffArray(rapidjson::kArrayType);
		for(int index = 0; index < _imu_buffer.get_length(); index++){
			imuSample & elem = _imu_buffer.get_data(index);
			{
				rapidjson::Value structObj(rapidjson::kObjectType);
				structObj.SetObject();
				if (isnan(elem.time_us)){
					structObj.AddMember("time_us", false, allocator);
				}else{
					structObj.AddMember("time_us", elem.time_us, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						arrayelem.PushBack(elem.delta_ang(i), allocator);
					}
					structObj.AddMember("delta_ang", arrayelem, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						arrayelem.PushBack(elem.delta_vel(i), allocator);
					}
					structObj.AddMember("delta_vel", arrayelem, allocator);
				}
				if (isnan(elem.delta_ang_dt)){
					structObj.AddMember("delta_ang_dt", false, allocator);
				}else{
					structObj.AddMember("delta_ang_dt", elem.delta_ang_dt, allocator);
				}
				if (isnan(elem.delta_vel_dt)){
					structObj.AddMember("delta_vel_dt", false, allocator);
				}else{
					structObj.AddMember("delta_vel_dt", elem.delta_vel_dt, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						arrayelem.PushBack(elem.delta_vel_clipping[i], allocator);
					}
					structObj.AddMember("delta_vel_clipping", arrayelem, allocator);
				}
				buffArray.PushBack(structObj, allocator);
			}
			}		imuSample_buffer.AddMember("_buffer", buffArray, allocator);
		ekfObj.AddMember("_imu_buffer", imuSample_buffer, allocator);
	}
	{
		rapidjson::Value outputSample_buffer(rapidjson::kObjectType);
		outputSample_buffer.AddMember("_head", _output_buffer.get_head(), allocator);
		outputSample_buffer.AddMember("_tail", _output_buffer.get_tail(), allocator);
		outputSample_buffer.AddMember("_size", _output_buffer.get_length(), allocator);
		outputSample_buffer.AddMember("_first_write", _output_buffer.get_first_write(), allocator);
		rapidjson::Value buffArray(rapidjson::kArrayType);
		for(int index = 0; index < _output_buffer.get_length(); index++){
			outputSample & elem = _output_buffer.get_data(index);
			{
				rapidjson::Value structObj(rapidjson::kObjectType);
				structObj.SetObject();
				if (isnan(elem.time_us)){
					structObj.AddMember("time_us", false, allocator);
				}else{
					structObj.AddMember("time_us", elem.time_us, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 4; i++){
						arrayelem.PushBack(elem.quat_nominal(i), allocator);
					}
					structObj.AddMember("quat_nominal", arrayelem, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						arrayelem.PushBack(elem.vel(i), allocator);
					}
					structObj.AddMember("vel", arrayelem, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						arrayelem.PushBack(elem.pos(i), allocator);
					}
					structObj.AddMember("pos", arrayelem, allocator);
				}
				buffArray.PushBack(structObj, allocator);
			}
			}		outputSample_buffer.AddMember("_buffer", buffArray, allocator);
		ekfObj.AddMember("_output_buffer", outputSample_buffer, allocator);
	}
	{
		rapidjson::Value outputVert_buffer(rapidjson::kObjectType);
		outputVert_buffer.AddMember("_head", _output_vert_buffer.get_head(), allocator);
		outputVert_buffer.AddMember("_tail", _output_vert_buffer.get_tail(), allocator);
		outputVert_buffer.AddMember("_size", _output_vert_buffer.get_length(), allocator);
		outputVert_buffer.AddMember("_first_write", _output_vert_buffer.get_first_write(), allocator);
		rapidjson::Value buffArray(rapidjson::kArrayType);
		for(int index = 0; index < _output_vert_buffer.get_length(); index++){
			outputVert & elem = _output_vert_buffer.get_data(index);
			{
				rapidjson::Value structObj(rapidjson::kObjectType);
				structObj.SetObject();
				if (isnan(elem.time_us)){
					structObj.AddMember("time_us", false, allocator);
				}else{
					structObj.AddMember("time_us", elem.time_us, allocator);
				}
				if (isnan(elem.vert_vel)){
					structObj.AddMember("vert_vel", false, allocator);
				}else{
					structObj.AddMember("vert_vel", elem.vert_vel, allocator);
				}
				if (isnan(elem.vert_vel_integ)){
					structObj.AddMember("vert_vel_integ", false, allocator);
				}else{
					structObj.AddMember("vert_vel_integ", elem.vert_vel_integ, allocator);
				}
				if (isnan(elem.dt)){
					structObj.AddMember("dt", false, allocator);
				}else{
					structObj.AddMember("dt", elem.dt, allocator);
				}
				buffArray.PushBack(structObj, allocator);
			}
			}		outputVert_buffer.AddMember("_buffer", buffArray, allocator);
		ekfObj.AddMember("_output_vert_buffer", outputVert_buffer, allocator);
	}
	if(_gps_buffer != nullptr){
		rapidjson::Value gpsSample_buffer(rapidjson::kObjectType);
		gpsSample_buffer.AddMember("_head", _gps_buffer->get_head(), allocator);
		gpsSample_buffer.AddMember("_tail", _gps_buffer->get_tail(), allocator);
		gpsSample_buffer.AddMember("_size", _gps_buffer->get_length(), allocator);
		gpsSample_buffer.AddMember("_first_write", _gps_buffer->get_first_write(), allocator);
		rapidjson::Value buffArray(rapidjson::kArrayType);
		for(int index = 0; index < _gps_buffer->get_length(); index++){
			gpsSample & elem = _gps_buffer->get_data(index);
			{
				rapidjson::Value structObj(rapidjson::kObjectType);
				structObj.SetObject();
				if (isnan(elem.time_us)){
					structObj.AddMember("time_us", false, allocator);
				}else{
					structObj.AddMember("time_us", elem.time_us, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 2; i++){
						arrayelem.PushBack(elem.pos(i), allocator);
					}
					structObj.AddMember("pos", arrayelem, allocator);
				}
				if (isnan(elem.hgt)){
					structObj.AddMember("hgt", false, allocator);
				}else{
					structObj.AddMember("hgt", elem.hgt, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						arrayelem.PushBack(elem.vel(i), allocator);
					}
					structObj.AddMember("vel", arrayelem, allocator);
				}
				if (isnan(elem.yaw)){
					structObj.AddMember("yaw", false, allocator);
				}else{
					structObj.AddMember("yaw", elem.yaw, allocator);
				}
				if (isnan(elem.hacc)){
					structObj.AddMember("hacc", false, allocator);
				}else{
					structObj.AddMember("hacc", elem.hacc, allocator);
				}
				if (isnan(elem.vacc)){
					structObj.AddMember("vacc", false, allocator);
				}else{
					structObj.AddMember("vacc", elem.vacc, allocator);
				}
				if (isnan(elem.sacc)){
					structObj.AddMember("sacc", false, allocator);
				}else{
					structObj.AddMember("sacc", elem.sacc, allocator);
				}
				buffArray.PushBack(structObj, allocator);
			}
			}		gpsSample_buffer.AddMember("_buffer", buffArray, allocator);
		ekfObj.AddMember("_gps_buffer", gpsSample_buffer, allocator);
	}
	if(_mag_buffer != nullptr){
		rapidjson::Value magSample_buffer(rapidjson::kObjectType);
		magSample_buffer.AddMember("_head", _mag_buffer->get_head(), allocator);
		magSample_buffer.AddMember("_tail", _mag_buffer->get_tail(), allocator);
		magSample_buffer.AddMember("_size", _mag_buffer->get_length(), allocator);
		magSample_buffer.AddMember("_first_write", _mag_buffer->get_first_write(), allocator);
		rapidjson::Value buffArray(rapidjson::kArrayType);
		for(int index = 0; index < _mag_buffer->get_length(); index++){
			magSample & elem = _mag_buffer->get_data(index);
			{
				rapidjson::Value structObj(rapidjson::kObjectType);
				structObj.SetObject();
				if (isnan(elem.time_us)){
					structObj.AddMember("time_us", false, allocator);
				}else{
					structObj.AddMember("time_us", elem.time_us, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						arrayelem.PushBack(elem.mag(i), allocator);
					}
					structObj.AddMember("mag", arrayelem, allocator);
				}
				buffArray.PushBack(structObj, allocator);
			}
			}		magSample_buffer.AddMember("_buffer", buffArray, allocator);
		ekfObj.AddMember("_mag_buffer", magSample_buffer, allocator);
	}
	if(_baro_buffer != nullptr){
		rapidjson::Value baroSample_buffer(rapidjson::kObjectType);
		baroSample_buffer.AddMember("_head", _baro_buffer->get_head(), allocator);
		baroSample_buffer.AddMember("_tail", _baro_buffer->get_tail(), allocator);
		baroSample_buffer.AddMember("_size", _baro_buffer->get_length(), allocator);
		baroSample_buffer.AddMember("_first_write", _baro_buffer->get_first_write(), allocator);
		rapidjson::Value buffArray(rapidjson::kArrayType);
		for(int index = 0; index < _baro_buffer->get_length(); index++){
			baroSample & elem = _baro_buffer->get_data(index);
			{
				rapidjson::Value structObj(rapidjson::kObjectType);
				structObj.SetObject();
				if (isnan(elem.time_us)){
					structObj.AddMember("time_us", false, allocator);
				}else{
					structObj.AddMember("time_us", elem.time_us, allocator);
				}
				if (isnan(elem.hgt)){
					structObj.AddMember("hgt", false, allocator);
				}else{
					structObj.AddMember("hgt", elem.hgt, allocator);
				}
				buffArray.PushBack(structObj, allocator);
			}
			}		baroSample_buffer.AddMember("_buffer", buffArray, allocator);
		ekfObj.AddMember("_baro_buffer", baroSample_buffer, allocator);
	}
	if(_range_buffer != nullptr){
		rapidjson::Value rangeSample_buffer(rapidjson::kObjectType);
		rangeSample_buffer.AddMember("_head", _range_buffer->get_head(), allocator);
		rangeSample_buffer.AddMember("_tail", _range_buffer->get_tail(), allocator);
		rangeSample_buffer.AddMember("_size", _range_buffer->get_length(), allocator);
		rangeSample_buffer.AddMember("_first_write", _range_buffer->get_first_write(), allocator);
		rapidjson::Value buffArray(rapidjson::kArrayType);
		for(int index = 0; index < _range_buffer->get_length(); index++){
			rangeSample & elem = _range_buffer->get_data(index);
			{
				rapidjson::Value structObj(rapidjson::kObjectType);
				structObj.SetObject();
				if (isnan(elem.time_us)){
					structObj.AddMember("time_us", false, allocator);
				}else{
					structObj.AddMember("time_us", elem.time_us, allocator);
				}
				if (isnan(elem.rng)){
					structObj.AddMember("rng", false, allocator);
				}else{
					structObj.AddMember("rng", elem.rng, allocator);
				}
				buffArray.PushBack(structObj, allocator);
			}
			}		rangeSample_buffer.AddMember("_buffer", buffArray, allocator);
		ekfObj.AddMember("_range_buffer", rangeSample_buffer, allocator);
	}
	if(_airspeed_buffer != nullptr){
		rapidjson::Value airspeedSample_buffer(rapidjson::kObjectType);
		airspeedSample_buffer.AddMember("_head", _airspeed_buffer->get_head(), allocator);
		airspeedSample_buffer.AddMember("_tail", _airspeed_buffer->get_tail(), allocator);
		airspeedSample_buffer.AddMember("_size", _airspeed_buffer->get_length(), allocator);
		airspeedSample_buffer.AddMember("_first_write", _airspeed_buffer->get_first_write(), allocator);
		rapidjson::Value buffArray(rapidjson::kArrayType);
		for(int index = 0; index < _airspeed_buffer->get_length(); index++){
			airspeedSample & elem = _airspeed_buffer->get_data(index);
			{
				rapidjson::Value structObj(rapidjson::kObjectType);
				structObj.SetObject();
				if (isnan(elem.time_us)){
					structObj.AddMember("time_us", false, allocator);
				}else{
					structObj.AddMember("time_us", elem.time_us, allocator);
				}
				if (isnan(elem.true_airspeed)){
					structObj.AddMember("true_airspeed", false, allocator);
				}else{
					structObj.AddMember("true_airspeed", elem.true_airspeed, allocator);
				}
				if (isnan(elem.eas2tas)){
					structObj.AddMember("eas2tas", false, allocator);
				}else{
					structObj.AddMember("eas2tas", elem.eas2tas, allocator);
				}
				buffArray.PushBack(structObj, allocator);
			}
			}		airspeedSample_buffer.AddMember("_buffer", buffArray, allocator);
		ekfObj.AddMember("_airspeed_buffer", airspeedSample_buffer, allocator);
	}
	if(_flow_buffer != nullptr){
		rapidjson::Value flowSample_buffer(rapidjson::kObjectType);
		flowSample_buffer.AddMember("_head", _flow_buffer->get_head(), allocator);
		flowSample_buffer.AddMember("_tail", _flow_buffer->get_tail(), allocator);
		flowSample_buffer.AddMember("_size", _flow_buffer->get_length(), allocator);
		flowSample_buffer.AddMember("_first_write", _flow_buffer->get_first_write(), allocator);
		rapidjson::Value buffArray(rapidjson::kArrayType);
		for(int index = 0; index < _flow_buffer->get_length(); index++){
			flowSample & elem = _flow_buffer->get_data(index);
			{
				rapidjson::Value structObj(rapidjson::kObjectType);
				structObj.SetObject();
				if (isnan(elem.time_us)){
					structObj.AddMember("time_us", false, allocator);
				}else{
					structObj.AddMember("time_us", elem.time_us, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 2; i++){
						arrayelem.PushBack(elem.flow_xy_rad(i), allocator);
					}
					structObj.AddMember("flow_xy_rad", arrayelem, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						arrayelem.PushBack(elem.gyro_xyz(i), allocator);
					}
					structObj.AddMember("gyro_xyz", arrayelem, allocator);
				}
				if (isnan(elem.dt)){
					structObj.AddMember("dt", false, allocator);
				}else{
					structObj.AddMember("dt", elem.dt, allocator);
				}
				if (isnan(elem.quality)){
					structObj.AddMember("quality", false, allocator);
				}else{
					structObj.AddMember("quality", elem.quality, allocator);
				}
				buffArray.PushBack(structObj, allocator);
			}
			}		flowSample_buffer.AddMember("_buffer", buffArray, allocator);
		ekfObj.AddMember("_flow_buffer", flowSample_buffer, allocator);
	}
	if(_ext_vision_buffer != nullptr){
		rapidjson::Value extVisionSample_buffer(rapidjson::kObjectType);
		extVisionSample_buffer.AddMember("_head", _ext_vision_buffer->get_head(), allocator);
		extVisionSample_buffer.AddMember("_tail", _ext_vision_buffer->get_tail(), allocator);
		extVisionSample_buffer.AddMember("_size", _ext_vision_buffer->get_length(), allocator);
		extVisionSample_buffer.AddMember("_first_write", _ext_vision_buffer->get_first_write(), allocator);
		rapidjson::Value buffArray(rapidjson::kArrayType);
		for(int index = 0; index < _ext_vision_buffer->get_length(); index++){
			extVisionSample & elem = _ext_vision_buffer->get_data(index);
			{
				rapidjson::Value structObj(rapidjson::kObjectType);
				structObj.SetObject();
				if (isnan(elem.time_us)){
					structObj.AddMember("time_us", false, allocator);
				}else{
					structObj.AddMember("time_us", elem.time_us, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						arrayelem.PushBack(elem.pos(i), allocator);
					}
					structObj.AddMember("pos", arrayelem, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						arrayelem.PushBack(elem.vel(i), allocator);
					}
					structObj.AddMember("vel", arrayelem, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 4; i++){
						arrayelem.PushBack(elem.quat(i), allocator);
					}
					structObj.AddMember("quat", arrayelem, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						arrayelem.PushBack(elem.posVar(i), allocator);
					}
					structObj.AddMember("posVar", arrayelem, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						for(int j = 0; j < 3; j++){
							arrayelem.PushBack(elem.velCov(i, j), allocator);
						}
					}
					structObj.AddMember("velCov", arrayelem, allocator);
				}
				if (isnan(elem.angVar)){
					structObj.AddMember("angVar", false, allocator);
				}else{
					structObj.AddMember("angVar", elem.angVar, allocator);
				}
				if (isnan(elem.reset_counter)){
					structObj.AddMember("reset_counter", false, allocator);
				}else{
					structObj.AddMember("reset_counter", elem.reset_counter, allocator);
				}
				buffArray.PushBack(structObj, allocator);
			}
			}		extVisionSample_buffer.AddMember("_buffer", buffArray, allocator);
		ekfObj.AddMember("_ext_vision_buffer", extVisionSample_buffer, allocator);
	}
	if(_drag_buffer != nullptr){
		rapidjson::Value dragSample_buffer(rapidjson::kObjectType);
		dragSample_buffer.AddMember("_head", _drag_buffer->get_head(), allocator);
		dragSample_buffer.AddMember("_tail", _drag_buffer->get_tail(), allocator);
		dragSample_buffer.AddMember("_size", _drag_buffer->get_length(), allocator);
		dragSample_buffer.AddMember("_first_write", _drag_buffer->get_first_write(), allocator);
		rapidjson::Value buffArray(rapidjson::kArrayType);
		for(int index = 0; index < _drag_buffer->get_length(); index++){
			dragSample & elem = _drag_buffer->get_data(index);
			{
				rapidjson::Value structObj(rapidjson::kObjectType);
				structObj.SetObject();
				if (isnan(elem.time_us)){
					structObj.AddMember("time_us", false, allocator);
				}else{
					structObj.AddMember("time_us", elem.time_us, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 2; i++){
						arrayelem.PushBack(elem.accelXY(i), allocator);
					}
					structObj.AddMember("accelXY", arrayelem, allocator);
				}
				buffArray.PushBack(structObj, allocator);
			}
			}		dragSample_buffer.AddMember("_buffer", buffArray, allocator);
		ekfObj.AddMember("_drag_buffer", dragSample_buffer, allocator);
	}
	if(_auxvel_buffer != nullptr){
		rapidjson::Value auxVelSample_buffer(rapidjson::kObjectType);
		auxVelSample_buffer.AddMember("_head", _auxvel_buffer->get_head(), allocator);
		auxVelSample_buffer.AddMember("_tail", _auxvel_buffer->get_tail(), allocator);
		auxVelSample_buffer.AddMember("_size", _auxvel_buffer->get_length(), allocator);
		auxVelSample_buffer.AddMember("_first_write", _auxvel_buffer->get_first_write(), allocator);
		rapidjson::Value buffArray(rapidjson::kArrayType);
		for(int index = 0; index < _auxvel_buffer->get_length(); index++){
			auxVelSample & elem = _auxvel_buffer->get_data(index);
			{
				rapidjson::Value structObj(rapidjson::kObjectType);
				structObj.SetObject();
				if (isnan(elem.time_us)){
					structObj.AddMember("time_us", false, allocator);
				}else{
					structObj.AddMember("time_us", elem.time_us, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						arrayelem.PushBack(elem.vel(i), allocator);
					}
					structObj.AddMember("vel", arrayelem, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						arrayelem.PushBack(elem.velVar(i), allocator);
					}
					structObj.AddMember("velVar", arrayelem, allocator);
				}
				buffArray.PushBack(structObj, allocator);
			}
			}		auxVelSample_buffer.AddMember("_buffer", buffArray, allocator);
		ekfObj.AddMember("_auxvel_buffer", auxVelSample_buffer, allocator);
	}
{
	if (isnan(_time_last_imu)){
		ekfObj.AddMember("_time_last_imu", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_imu", _time_last_imu, allocator);
	}
}
{
	if (isnan(_time_last_gps)){
		ekfObj.AddMember("_time_last_gps", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_gps", _time_last_gps, allocator);
	}
}
{
	if (isnan(_time_last_mag)){
		ekfObj.AddMember("_time_last_mag", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_mag", _time_last_mag, allocator);
	}
}
{
	if (isnan(_time_last_baro)){
		ekfObj.AddMember("_time_last_baro", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_baro", _time_last_baro, allocator);
	}
}
{
	if (isnan(_time_last_range)){
		ekfObj.AddMember("_time_last_range", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_range", _time_last_range, allocator);
	}
}
{
	if (isnan(_time_last_airspeed)){
		ekfObj.AddMember("_time_last_airspeed", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_airspeed", _time_last_airspeed, allocator);
	}
}
{
	if (isnan(_time_last_ext_vision)){
		ekfObj.AddMember("_time_last_ext_vision", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_ext_vision", _time_last_ext_vision, allocator);
	}
}
{
	if (isnan(_time_last_optflow)){
		ekfObj.AddMember("_time_last_optflow", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_optflow", _time_last_optflow, allocator);
	}
}
{
	if (isnan(_time_last_auxvel)){
		ekfObj.AddMember("_time_last_auxvel", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_auxvel", _time_last_auxvel, allocator);
	}
}
{
	if (isnan(_time_last_gnd_effect_on)){
		ekfObj.AddMember("_time_last_gnd_effect_on", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_gnd_effect_on", _time_last_gnd_effect_on, allocator);
	}
}
	{
		rapidjson::Value unionJson(rapidjson::kObjectType);
		rapidjson::Value innerJson(rapidjson::kObjectType);
		innerJson.AddMember("bad_acc_bias", _fault_status.flags.bad_acc_bias, allocator);
		innerJson.AddMember("bad_acc_clipping", _fault_status.flags.bad_acc_clipping, allocator);
		innerJson.AddMember("bad_acc_vertical", _fault_status.flags.bad_acc_vertical, allocator);
		innerJson.AddMember("bad_airspeed", _fault_status.flags.bad_airspeed, allocator);
		innerJson.AddMember("bad_hdg", _fault_status.flags.bad_hdg, allocator);
		innerJson.AddMember("bad_mag_decl", _fault_status.flags.bad_mag_decl, allocator);
		innerJson.AddMember("bad_mag_x", _fault_status.flags.bad_mag_x, allocator);
		innerJson.AddMember("bad_mag_y", _fault_status.flags.bad_mag_y, allocator);
		innerJson.AddMember("bad_mag_z", _fault_status.flags.bad_mag_z, allocator);
		innerJson.AddMember("bad_optflow_X", _fault_status.flags.bad_optflow_X, allocator);
		innerJson.AddMember("bad_optflow_Y", _fault_status.flags.bad_optflow_Y, allocator);
		innerJson.AddMember("bad_pos_D", _fault_status.flags.bad_pos_D, allocator);
		innerJson.AddMember("bad_pos_E", _fault_status.flags.bad_pos_E, allocator);
		innerJson.AddMember("bad_pos_N", _fault_status.flags.bad_pos_N, allocator);
		innerJson.AddMember("bad_sideslip", _fault_status.flags.bad_sideslip, allocator);
		innerJson.AddMember("bad_vel_D", _fault_status.flags.bad_vel_D, allocator);
		innerJson.AddMember("bad_vel_E", _fault_status.flags.bad_vel_E, allocator);
		innerJson.AddMember("bad_vel_N", _fault_status.flags.bad_vel_N, allocator);
		unionJson.AddMember("flags", innerJson, allocator);
		ekfObj.AddMember("_fault_status", unionJson, allocator);
	}{
	if (isnan(_mag_declination_gps)){
		ekfObj.AddMember("_mag_declination_gps", false, allocator);
	}else{
		ekfObj.AddMember("_mag_declination_gps", _mag_declination_gps, allocator);
	}
}
{
	if (isnan(_mag_inclination_gps)){
		ekfObj.AddMember("_mag_inclination_gps", false, allocator);
	}else{
		ekfObj.AddMember("_mag_inclination_gps", _mag_inclination_gps, allocator);
	}
}
{
	if (isnan(_mag_strength_gps)){
		ekfObj.AddMember("_mag_strength_gps", false, allocator);
	}else{
		ekfObj.AddMember("_mag_strength_gps", _mag_strength_gps, allocator);
	}
}
	{
		rapidjson::Value unionJson(rapidjson::kObjectType);
		rapidjson::Value innerJson(rapidjson::kObjectType);
		if(_control_status.flags.baro_hgt){
			innerJson.AddMember("baro_hgt", true, allocator);
		}else{
			innerJson.AddMember("baro_hgt", false, allocator);
		}
		if(_control_status.flags.ev_hgt){
			innerJson.AddMember("ev_hgt", true, allocator);
		}else{
			innerJson.AddMember("ev_hgt", false, allocator);
		}
		if(_control_status.flags.ev_pos){
			innerJson.AddMember("ev_pos", true, allocator);
		}else{
			innerJson.AddMember("ev_pos", false, allocator);
		}
		if(_control_status.flags.ev_vel){
			innerJson.AddMember("ev_vel", true, allocator);
		}else{
			innerJson.AddMember("ev_vel", false, allocator);
		}
		if(_control_status.flags.ev_yaw){
			innerJson.AddMember("ev_yaw", true, allocator);
		}else{
			innerJson.AddMember("ev_yaw", false, allocator);
		}
		if(_control_status.flags.fixed_wing){
			innerJson.AddMember("fixed_wing", true, allocator);
		}else{
			innerJson.AddMember("fixed_wing", false, allocator);
		}
		if(_control_status.flags.fuse_aspd){
			innerJson.AddMember("fuse_aspd", true, allocator);
		}else{
			innerJson.AddMember("fuse_aspd", false, allocator);
		}
		if(_control_status.flags.fuse_beta){
			innerJson.AddMember("fuse_beta", true, allocator);
		}else{
			innerJson.AddMember("fuse_beta", false, allocator);
		}
		if(_control_status.flags.gnd_effect){
			innerJson.AddMember("gnd_effect", true, allocator);
		}else{
			innerJson.AddMember("gnd_effect", false, allocator);
		}
		if(_control_status.flags.gps){
			innerJson.AddMember("gps", true, allocator);
		}else{
			innerJson.AddMember("gps", false, allocator);
		}
		if(_control_status.flags.gps_hgt){
			innerJson.AddMember("gps_hgt", true, allocator);
		}else{
			innerJson.AddMember("gps_hgt", false, allocator);
		}
		if(_control_status.flags.gps_yaw){
			innerJson.AddMember("gps_yaw", true, allocator);
		}else{
			innerJson.AddMember("gps_yaw", false, allocator);
		}
		if(_control_status.flags.gps_yaw_fault){
			innerJson.AddMember("gps_yaw_fault", true, allocator);
		}else{
			innerJson.AddMember("gps_yaw_fault", false, allocator);
		}
		if(_control_status.flags.in_air){
			innerJson.AddMember("in_air", true, allocator);
		}else{
			innerJson.AddMember("in_air", false, allocator);
		}
		if(_control_status.flags.inertial_dead_reckoning){
			innerJson.AddMember("inertial_dead_reckoning", true, allocator);
		}else{
			innerJson.AddMember("inertial_dead_reckoning", false, allocator);
		}
		if(_control_status.flags.mag_3D){
			innerJson.AddMember("mag_3D", true, allocator);
		}else{
			innerJson.AddMember("mag_3D", false, allocator);
		}
		if(_control_status.flags.mag_aligned_in_flight){
			innerJson.AddMember("mag_aligned_in_flight", true, allocator);
		}else{
			innerJson.AddMember("mag_aligned_in_flight", false, allocator);
		}
		if(_control_status.flags.mag_dec){
			innerJson.AddMember("mag_dec", true, allocator);
		}else{
			innerJson.AddMember("mag_dec", false, allocator);
		}
		if(_control_status.flags.mag_fault){
			innerJson.AddMember("mag_fault", true, allocator);
		}else{
			innerJson.AddMember("mag_fault", false, allocator);
		}
		if(_control_status.flags.mag_field_disturbed){
			innerJson.AddMember("mag_field_disturbed", true, allocator);
		}else{
			innerJson.AddMember("mag_field_disturbed", false, allocator);
		}
		if(_control_status.flags.mag_hdg){
			innerJson.AddMember("mag_hdg", true, allocator);
		}else{
			innerJson.AddMember("mag_hdg", false, allocator);
		}
		if(_control_status.flags.opt_flow){
			innerJson.AddMember("opt_flow", true, allocator);
		}else{
			innerJson.AddMember("opt_flow", false, allocator);
		}
		if(_control_status.flags.rng_fault){
			innerJson.AddMember("rng_fault", true, allocator);
		}else{
			innerJson.AddMember("rng_fault", false, allocator);
		}
		if(_control_status.flags.rng_hgt){
			innerJson.AddMember("rng_hgt", true, allocator);
		}else{
			innerJson.AddMember("rng_hgt", false, allocator);
		}
		if(_control_status.flags.rng_kin_consistent){
			innerJson.AddMember("rng_kin_consistent", true, allocator);
		}else{
			innerJson.AddMember("rng_kin_consistent", false, allocator);
		}
		if(_control_status.flags.rng_stuck){
			innerJson.AddMember("rng_stuck", true, allocator);
		}else{
			innerJson.AddMember("rng_stuck", false, allocator);
		}
		if(_control_status.flags.synthetic_mag_z){
			innerJson.AddMember("synthetic_mag_z", true, allocator);
		}else{
			innerJson.AddMember("synthetic_mag_z", false, allocator);
		}
		if(_control_status.flags.tilt_align){
			innerJson.AddMember("tilt_align", true, allocator);
		}else{
			innerJson.AddMember("tilt_align", false, allocator);
		}
		if(_control_status.flags.vehicle_at_rest){
			innerJson.AddMember("vehicle_at_rest", true, allocator);
		}else{
			innerJson.AddMember("vehicle_at_rest", false, allocator);
		}
		if(_control_status.flags.wind){
			innerJson.AddMember("wind", true, allocator);
		}else{
			innerJson.AddMember("wind", false, allocator);
		}
		if(_control_status.flags.wind_dead_reckoning){
			innerJson.AddMember("wind_dead_reckoning", true, allocator);
		}else{
			innerJson.AddMember("wind_dead_reckoning", false, allocator);
		}
		if(_control_status.flags.yaw_align){
			innerJson.AddMember("yaw_align", true, allocator);
		}else{
			innerJson.AddMember("yaw_align", false, allocator);
		}
		unionJson.AddMember("flags", innerJson, allocator);
		ekfObj.AddMember("_control_status", unionJson, allocator);
	}	{
		rapidjson::Value unionJson(rapidjson::kObjectType);
		rapidjson::Value innerJson(rapidjson::kObjectType);
		if(_control_status_prev.flags.baro_hgt){
			innerJson.AddMember("baro_hgt", true, allocator);
		}else{
			innerJson.AddMember("baro_hgt", false, allocator);
		}
		if(_control_status_prev.flags.ev_hgt){
			innerJson.AddMember("ev_hgt", true, allocator);
		}else{
			innerJson.AddMember("ev_hgt", false, allocator);
		}
		if(_control_status_prev.flags.ev_pos){
			innerJson.AddMember("ev_pos", true, allocator);
		}else{
			innerJson.AddMember("ev_pos", false, allocator);
		}
		if(_control_status_prev.flags.ev_vel){
			innerJson.AddMember("ev_vel", true, allocator);
		}else{
			innerJson.AddMember("ev_vel", false, allocator);
		}
		if(_control_status_prev.flags.ev_yaw){
			innerJson.AddMember("ev_yaw", true, allocator);
		}else{
			innerJson.AddMember("ev_yaw", false, allocator);
		}
		if(_control_status_prev.flags.fixed_wing){
			innerJson.AddMember("fixed_wing", true, allocator);
		}else{
			innerJson.AddMember("fixed_wing", false, allocator);
		}
		if(_control_status_prev.flags.fuse_aspd){
			innerJson.AddMember("fuse_aspd", true, allocator);
		}else{
			innerJson.AddMember("fuse_aspd", false, allocator);
		}
		if(_control_status_prev.flags.fuse_beta){
			innerJson.AddMember("fuse_beta", true, allocator);
		}else{
			innerJson.AddMember("fuse_beta", false, allocator);
		}
		if(_control_status_prev.flags.gnd_effect){
			innerJson.AddMember("gnd_effect", true, allocator);
		}else{
			innerJson.AddMember("gnd_effect", false, allocator);
		}
		if(_control_status_prev.flags.gps){
			innerJson.AddMember("gps", true, allocator);
		}else{
			innerJson.AddMember("gps", false, allocator);
		}
		if(_control_status_prev.flags.gps_hgt){
			innerJson.AddMember("gps_hgt", true, allocator);
		}else{
			innerJson.AddMember("gps_hgt", false, allocator);
		}
		if(_control_status_prev.flags.gps_yaw){
			innerJson.AddMember("gps_yaw", true, allocator);
		}else{
			innerJson.AddMember("gps_yaw", false, allocator);
		}
		if(_control_status_prev.flags.gps_yaw_fault){
			innerJson.AddMember("gps_yaw_fault", true, allocator);
		}else{
			innerJson.AddMember("gps_yaw_fault", false, allocator);
		}
		if(_control_status_prev.flags.in_air){
			innerJson.AddMember("in_air", true, allocator);
		}else{
			innerJson.AddMember("in_air", false, allocator);
		}
		if(_control_status_prev.flags.inertial_dead_reckoning){
			innerJson.AddMember("inertial_dead_reckoning", true, allocator);
		}else{
			innerJson.AddMember("inertial_dead_reckoning", false, allocator);
		}
		if(_control_status_prev.flags.mag_3D){
			innerJson.AddMember("mag_3D", true, allocator);
		}else{
			innerJson.AddMember("mag_3D", false, allocator);
		}
		if(_control_status_prev.flags.mag_aligned_in_flight){
			innerJson.AddMember("mag_aligned_in_flight", true, allocator);
		}else{
			innerJson.AddMember("mag_aligned_in_flight", false, allocator);
		}
		if(_control_status_prev.flags.mag_dec){
			innerJson.AddMember("mag_dec", true, allocator);
		}else{
			innerJson.AddMember("mag_dec", false, allocator);
		}
		if(_control_status_prev.flags.mag_fault){
			innerJson.AddMember("mag_fault", true, allocator);
		}else{
			innerJson.AddMember("mag_fault", false, allocator);
		}
		if(_control_status_prev.flags.mag_field_disturbed){
			innerJson.AddMember("mag_field_disturbed", true, allocator);
		}else{
			innerJson.AddMember("mag_field_disturbed", false, allocator);
		}
		if(_control_status_prev.flags.mag_hdg){
			innerJson.AddMember("mag_hdg", true, allocator);
		}else{
			innerJson.AddMember("mag_hdg", false, allocator);
		}
		if(_control_status_prev.flags.opt_flow){
			innerJson.AddMember("opt_flow", true, allocator);
		}else{
			innerJson.AddMember("opt_flow", false, allocator);
		}
		if(_control_status_prev.flags.rng_fault){
			innerJson.AddMember("rng_fault", true, allocator);
		}else{
			innerJson.AddMember("rng_fault", false, allocator);
		}
		if(_control_status_prev.flags.rng_hgt){
			innerJson.AddMember("rng_hgt", true, allocator);
		}else{
			innerJson.AddMember("rng_hgt", false, allocator);
		}
		if(_control_status_prev.flags.rng_kin_consistent){
			innerJson.AddMember("rng_kin_consistent", true, allocator);
		}else{
			innerJson.AddMember("rng_kin_consistent", false, allocator);
		}
		if(_control_status_prev.flags.rng_stuck){
			innerJson.AddMember("rng_stuck", true, allocator);
		}else{
			innerJson.AddMember("rng_stuck", false, allocator);
		}
		if(_control_status_prev.flags.synthetic_mag_z){
			innerJson.AddMember("synthetic_mag_z", true, allocator);
		}else{
			innerJson.AddMember("synthetic_mag_z", false, allocator);
		}
		if(_control_status_prev.flags.tilt_align){
			innerJson.AddMember("tilt_align", true, allocator);
		}else{
			innerJson.AddMember("tilt_align", false, allocator);
		}
		if(_control_status_prev.flags.vehicle_at_rest){
			innerJson.AddMember("vehicle_at_rest", true, allocator);
		}else{
			innerJson.AddMember("vehicle_at_rest", false, allocator);
		}
		if(_control_status_prev.flags.wind){
			innerJson.AddMember("wind", true, allocator);
		}else{
			innerJson.AddMember("wind", false, allocator);
		}
		if(_control_status_prev.flags.wind_dead_reckoning){
			innerJson.AddMember("wind_dead_reckoning", true, allocator);
		}else{
			innerJson.AddMember("wind_dead_reckoning", false, allocator);
		}
		if(_control_status_prev.flags.yaw_align){
			innerJson.AddMember("yaw_align", true, allocator);
		}else{
			innerJson.AddMember("yaw_align", false, allocator);
		}
		unionJson.AddMember("flags", innerJson, allocator);
		ekfObj.AddMember("_control_status_prev", unionJson, allocator);
	}	{
		rapidjson::Value unionJson(rapidjson::kObjectType);
		rapidjson::Value innerJson(rapidjson::kObjectType);
		innerJson.AddMember("bad_yaw_using_gps_course", _warning_events.flags.bad_yaw_using_gps_course, allocator);
		innerJson.AddMember("emergency_yaw_reset_gps_yaw_stopped", _warning_events.flags.emergency_yaw_reset_gps_yaw_stopped, allocator);
		innerJson.AddMember("emergency_yaw_reset_mag_stopped", _warning_events.flags.emergency_yaw_reset_mag_stopped, allocator);
		innerJson.AddMember("gps_data_stopped", _warning_events.flags.gps_data_stopped, allocator);
		innerJson.AddMember("gps_data_stopped_using_alternate", _warning_events.flags.gps_data_stopped_using_alternate, allocator);
		innerJson.AddMember("gps_fusion_timout", _warning_events.flags.gps_fusion_timout, allocator);
		innerJson.AddMember("gps_quality_poor", _warning_events.flags.gps_quality_poor, allocator);
		innerJson.AddMember("height_sensor_timeout", _warning_events.flags.height_sensor_timeout, allocator);
		innerJson.AddMember("invalid_accel_bias_cov_reset", _warning_events.flags.invalid_accel_bias_cov_reset, allocator);
		innerJson.AddMember("stopping_mag_use", _warning_events.flags.stopping_mag_use, allocator);
		innerJson.AddMember("stopping_navigation", _warning_events.flags.stopping_navigation, allocator);
		innerJson.AddMember("vision_data_stopped", _warning_events.flags.vision_data_stopped, allocator);
		unionJson.AddMember("flags", innerJson, allocator);
		ekfObj.AddMember("_warning_events", unionJson, allocator);
	}	{
		rapidjson::Value unionJson(rapidjson::kObjectType);
		rapidjson::Value innerJson(rapidjson::kObjectType);
		innerJson.AddMember("gps_checks_passed", _information_events.flags.gps_checks_passed, allocator);
		innerJson.AddMember("reset_pos_to_gps", _information_events.flags.reset_pos_to_gps, allocator);
		innerJson.AddMember("reset_pos_to_last_known", _information_events.flags.reset_pos_to_last_known, allocator);
		innerJson.AddMember("reset_pos_to_vision", _information_events.flags.reset_pos_to_vision, allocator);
		innerJson.AddMember("reset_vel_to_flow", _information_events.flags.reset_vel_to_flow, allocator);
		innerJson.AddMember("reset_vel_to_gps", _information_events.flags.reset_vel_to_gps, allocator);
		innerJson.AddMember("reset_vel_to_vision", _information_events.flags.reset_vel_to_vision, allocator);
		innerJson.AddMember("reset_vel_to_zero", _information_events.flags.reset_vel_to_zero, allocator);
		innerJson.AddMember("starting_gps_fusion", _information_events.flags.starting_gps_fusion, allocator);
		innerJson.AddMember("starting_vision_pos_fusion", _information_events.flags.starting_vision_pos_fusion, allocator);
		innerJson.AddMember("starting_vision_vel_fusion", _information_events.flags.starting_vision_vel_fusion, allocator);
		innerJson.AddMember("starting_vision_yaw_fusion", _information_events.flags.starting_vision_yaw_fusion, allocator);
		innerJson.AddMember("yaw_aligned_to_imu_gps", _information_events.flags.yaw_aligned_to_imu_gps, allocator);
		unionJson.AddMember("flags", innerJson, allocator);
		ekfObj.AddMember("_information_events", unionJson, allocator);
	}{
}
{
	if (isnan(_min_obs_interval_us)){
		ekfObj.AddMember("_min_obs_interval_us", false, allocator);
	}else{
		ekfObj.AddMember("_min_obs_interval_us", _min_obs_interval_us, allocator);
	}
}
{
	if (isnan(_drag_sample_count)){
		ekfObj.AddMember("_drag_sample_count", false, allocator);
	}else{
		ekfObj.AddMember("_drag_sample_count", _drag_sample_count, allocator);
	}
}
{
	if (isnan(_drag_sample_time_dt)){
		ekfObj.AddMember("_drag_sample_time_dt", false, allocator);
	}else{
		ekfObj.AddMember("_drag_sample_time_dt", _drag_sample_time_dt, allocator);
	}
}

}
void EstimatorInterface::checkJson(rapidjson::Value & ekfObj){
{
	assert(ekfObj["_params"].IsObject());
	assert(ekfObj["_params"]["filter_update_interval_us"].IsInt());
	assert(ekfObj["_params"]["fusion_mode"].IsInt());
	assert(ekfObj["_params"]["vdist_sensor_type"].IsInt());
	assert(ekfObj["_params"]["terrain_fusion_mode"].IsInt());
	assert(ekfObj["_params"]["sensor_interval_max_ms"].IsInt());
	assert(ekfObj["_params"]["mag_delay_ms"].IsFloat() || ekfObj["_params"]["mag_delay_ms"].IsBool());
	assert(ekfObj["_params"]["baro_delay_ms"].IsFloat() || ekfObj["_params"]["baro_delay_ms"].IsBool());
	assert(ekfObj["_params"]["gps_delay_ms"].IsFloat() || ekfObj["_params"]["gps_delay_ms"].IsBool());
	assert(ekfObj["_params"]["airspeed_delay_ms"].IsFloat() || ekfObj["_params"]["airspeed_delay_ms"].IsBool());
	assert(ekfObj["_params"]["flow_delay_ms"].IsFloat() || ekfObj["_params"]["flow_delay_ms"].IsBool());
	assert(ekfObj["_params"]["range_delay_ms"].IsFloat() || ekfObj["_params"]["range_delay_ms"].IsBool());
	assert(ekfObj["_params"]["ev_delay_ms"].IsFloat() || ekfObj["_params"]["ev_delay_ms"].IsBool());
	assert(ekfObj["_params"]["auxvel_delay_ms"].IsFloat() || ekfObj["_params"]["auxvel_delay_ms"].IsBool());
	assert(ekfObj["_params"]["gyro_noise"].IsFloat() || ekfObj["_params"]["gyro_noise"].IsBool());
	assert(ekfObj["_params"]["accel_noise"].IsFloat() || ekfObj["_params"]["accel_noise"].IsBool());
	assert(ekfObj["_params"]["gyro_bias_p_noise"].IsFloat() || ekfObj["_params"]["gyro_bias_p_noise"].IsBool());
	assert(ekfObj["_params"]["accel_bias_p_noise"].IsFloat() || ekfObj["_params"]["accel_bias_p_noise"].IsBool());
	assert(ekfObj["_params"]["mage_p_noise"].IsFloat() || ekfObj["_params"]["mage_p_noise"].IsBool());
	assert(ekfObj["_params"]["magb_p_noise"].IsFloat() || ekfObj["_params"]["magb_p_noise"].IsBool());
	assert(ekfObj["_params"]["wind_vel_p_noise"].IsFloat() || ekfObj["_params"]["wind_vel_p_noise"].IsBool());
	assert(ekfObj["_params"]["terrain_p_noise"].IsFloat() || ekfObj["_params"]["terrain_p_noise"].IsBool());
	assert(ekfObj["_params"]["terrain_gradient"].IsFloat() || ekfObj["_params"]["terrain_gradient"].IsBool());
	assert(ekfObj["_params"]["switch_on_gyro_bias"].IsFloat() || ekfObj["_params"]["switch_on_gyro_bias"].IsBool());
	assert(ekfObj["_params"]["switch_on_accel_bias"].IsFloat() || ekfObj["_params"]["switch_on_accel_bias"].IsBool());
	assert(ekfObj["_params"]["initial_tilt_err"].IsFloat() || ekfObj["_params"]["initial_tilt_err"].IsBool());
	assert(ekfObj["_params"]["gps_vel_noise"].IsFloat() || ekfObj["_params"]["gps_vel_noise"].IsBool());
	assert(ekfObj["_params"]["gps_pos_noise"].IsFloat() || ekfObj["_params"]["gps_pos_noise"].IsBool());
	assert(ekfObj["_params"]["pos_noaid_noise"].IsFloat() || ekfObj["_params"]["pos_noaid_noise"].IsBool());
	assert(ekfObj["_params"]["baro_noise"].IsFloat() || ekfObj["_params"]["baro_noise"].IsBool());
	assert(ekfObj["_params"]["baro_drift_rate"].IsFloat() || ekfObj["_params"]["baro_drift_rate"].IsBool());
	assert(ekfObj["_params"]["baro_innov_gate"].IsFloat() || ekfObj["_params"]["baro_innov_gate"].IsBool());
	assert(ekfObj["_params"]["gps_pos_innov_gate"].IsFloat() || ekfObj["_params"]["gps_pos_innov_gate"].IsBool());
	assert(ekfObj["_params"]["gps_vel_innov_gate"].IsFloat() || ekfObj["_params"]["gps_vel_innov_gate"].IsBool());
	assert(ekfObj["_params"]["gnd_effect_deadzone"].IsFloat() || ekfObj["_params"]["gnd_effect_deadzone"].IsBool());
	assert(ekfObj["_params"]["gnd_effect_max_hgt"].IsFloat() || ekfObj["_params"]["gnd_effect_max_hgt"].IsBool());
	assert(ekfObj["_params"]["mag_heading_noise"].IsFloat() || ekfObj["_params"]["mag_heading_noise"].IsBool());
	assert(ekfObj["_params"]["mag_noise"].IsFloat() || ekfObj["_params"]["mag_noise"].IsBool());
	assert(ekfObj["_params"]["mag_declination_deg"].IsFloat() || ekfObj["_params"]["mag_declination_deg"].IsBool());
	assert(ekfObj["_params"]["heading_innov_gate"].IsFloat() || ekfObj["_params"]["heading_innov_gate"].IsBool());
	assert(ekfObj["_params"]["mag_innov_gate"].IsFloat() || ekfObj["_params"]["mag_innov_gate"].IsBool());
	assert(ekfObj["_params"]["mag_declination_source"].IsInt());
	assert(ekfObj["_params"]["mag_fusion_type"].IsInt());
	assert(ekfObj["_params"]["mag_acc_gate"].IsFloat() || ekfObj["_params"]["mag_acc_gate"].IsBool());
	assert(ekfObj["_params"]["mag_yaw_rate_gate"].IsFloat() || ekfObj["_params"]["mag_yaw_rate_gate"].IsBool());
	assert(ekfObj["_params"]["gps_heading_noise"].IsFloat() || ekfObj["_params"]["gps_heading_noise"].IsBool());
	assert(ekfObj["_params"]["tas_innov_gate"].IsFloat() || ekfObj["_params"]["tas_innov_gate"].IsBool());
	assert(ekfObj["_params"]["eas_noise"].IsFloat() || ekfObj["_params"]["eas_noise"].IsBool());
	assert(ekfObj["_params"]["arsp_thr"].IsFloat() || ekfObj["_params"]["arsp_thr"].IsBool());
	assert(ekfObj["_params"]["beta_innov_gate"].IsFloat() || ekfObj["_params"]["beta_innov_gate"].IsBool());
	assert(ekfObj["_params"]["beta_noise"].IsFloat() || ekfObj["_params"]["beta_noise"].IsBool());
	assert(ekfObj["_params"]["range_noise"].IsFloat() || ekfObj["_params"]["range_noise"].IsBool());
	assert(ekfObj["_params"]["range_innov_gate"].IsFloat() || ekfObj["_params"]["range_innov_gate"].IsBool());
	assert(ekfObj["_params"]["rng_gnd_clearance"].IsFloat() || ekfObj["_params"]["rng_gnd_clearance"].IsBool());
	assert(ekfObj["_params"]["rng_sens_pitch"].IsFloat() || ekfObj["_params"]["rng_sens_pitch"].IsBool());
	assert(ekfObj["_params"]["range_noise_scaler"].IsFloat() || ekfObj["_params"]["range_noise_scaler"].IsBool());
	assert(ekfObj["_params"]["max_hagl_for_range_aid"].IsFloat() || ekfObj["_params"]["max_hagl_for_range_aid"].IsBool());
	assert(ekfObj["_params"]["max_vel_for_range_aid"].IsFloat() || ekfObj["_params"]["max_vel_for_range_aid"].IsBool());
	assert(ekfObj["_params"]["range_aid"].IsInt());
	assert(ekfObj["_params"]["range_aid_innov_gate"].IsFloat() || ekfObj["_params"]["range_aid_innov_gate"].IsBool());
	assert(ekfObj["_params"]["range_valid_quality_s"].IsFloat() || ekfObj["_params"]["range_valid_quality_s"].IsBool());
	assert(ekfObj["_params"]["range_cos_max_tilt"].IsFloat() || ekfObj["_params"]["range_cos_max_tilt"].IsBool());
	assert(ekfObj["_params"]["range_kin_consistency_gate"].IsFloat() || ekfObj["_params"]["range_kin_consistency_gate"].IsBool());
	assert(ekfObj["_params"]["ev_vel_innov_gate"].IsFloat() || ekfObj["_params"]["ev_vel_innov_gate"].IsBool());
	assert(ekfObj["_params"]["ev_pos_innov_gate"].IsFloat() || ekfObj["_params"]["ev_pos_innov_gate"].IsBool());
	assert(ekfObj["_params"]["flow_noise"].IsFloat() || ekfObj["_params"]["flow_noise"].IsBool());
	assert(ekfObj["_params"]["flow_noise_qual_min"].IsFloat() || ekfObj["_params"]["flow_noise_qual_min"].IsBool());
	assert(ekfObj["_params"]["flow_qual_min"].IsInt());
	assert(ekfObj["_params"]["flow_innov_gate"].IsFloat() || ekfObj["_params"]["flow_innov_gate"].IsBool());
	assert(ekfObj["_params"]["gps_check_mask"].IsInt());
	assert(ekfObj["_params"]["req_hacc"].IsFloat() || ekfObj["_params"]["req_hacc"].IsBool());
	assert(ekfObj["_params"]["req_vacc"].IsFloat() || ekfObj["_params"]["req_vacc"].IsBool());
	assert(ekfObj["_params"]["req_sacc"].IsFloat() || ekfObj["_params"]["req_sacc"].IsBool());
	assert(ekfObj["_params"]["req_nsats"].IsInt());
	assert(ekfObj["_params"]["req_pdop"].IsFloat() || ekfObj["_params"]["req_pdop"].IsBool());
	assert(ekfObj["_params"]["req_hdrift"].IsFloat() || ekfObj["_params"]["req_hdrift"].IsBool());
	assert(ekfObj["_params"]["req_vdrift"].IsFloat() || ekfObj["_params"]["req_vdrift"].IsBool());
	assert(ekfObj["_params"]["imu_pos_body"].IsArray());
	assert(ekfObj["_params"]["gps_pos_body"].IsArray());
	assert(ekfObj["_params"]["rng_pos_body"].IsArray());
	assert(ekfObj["_params"]["flow_pos_body"].IsArray());
	assert(ekfObj["_params"]["ev_pos_body"].IsArray());
	assert(ekfObj["_params"]["vel_Tau"].IsFloat() || ekfObj["_params"]["vel_Tau"].IsBool());
	assert(ekfObj["_params"]["pos_Tau"].IsFloat() || ekfObj["_params"]["pos_Tau"].IsBool());
	assert(ekfObj["_params"]["acc_bias_lim"].IsFloat() || ekfObj["_params"]["acc_bias_lim"].IsBool());
	assert(ekfObj["_params"]["acc_bias_learn_acc_lim"].IsFloat() || ekfObj["_params"]["acc_bias_learn_acc_lim"].IsBool());
	assert(ekfObj["_params"]["acc_bias_learn_gyr_lim"].IsFloat() || ekfObj["_params"]["acc_bias_learn_gyr_lim"].IsBool());
	assert(ekfObj["_params"]["acc_bias_learn_tc"].IsFloat() || ekfObj["_params"]["acc_bias_learn_tc"].IsBool());
	assert(ekfObj["_params"]["valid_timeout_max"].IsInt());
	assert(ekfObj["_params"]["static_pressure_coef_xp"].IsFloat() || ekfObj["_params"]["static_pressure_coef_xp"].IsBool());
	assert(ekfObj["_params"]["static_pressure_coef_xn"].IsFloat() || ekfObj["_params"]["static_pressure_coef_xn"].IsBool());
	assert(ekfObj["_params"]["static_pressure_coef_yp"].IsFloat() || ekfObj["_params"]["static_pressure_coef_yp"].IsBool());
	assert(ekfObj["_params"]["static_pressure_coef_yn"].IsFloat() || ekfObj["_params"]["static_pressure_coef_yn"].IsBool());
	assert(ekfObj["_params"]["static_pressure_coef_z"].IsFloat() || ekfObj["_params"]["static_pressure_coef_z"].IsBool());
	assert(ekfObj["_params"]["max_correction_airspeed"].IsFloat() || ekfObj["_params"]["max_correction_airspeed"].IsBool());
	assert(ekfObj["_params"]["drag_noise"].IsFloat() || ekfObj["_params"]["drag_noise"].IsBool());
	assert(ekfObj["_params"]["bcoef_x"].IsFloat() || ekfObj["_params"]["bcoef_x"].IsBool());
	assert(ekfObj["_params"]["bcoef_y"].IsFloat() || ekfObj["_params"]["bcoef_y"].IsBool());
	assert(ekfObj["_params"]["mcoef"].IsFloat() || ekfObj["_params"]["mcoef"].IsBool());
	assert(ekfObj["_params"]["synthesize_mag_z"].IsInt());
	assert(ekfObj["_params"]["check_mag_strength"].IsInt());
	assert(ekfObj["_params"]["EKFGSF_tas_default"].IsFloat() || ekfObj["_params"]["EKFGSF_tas_default"].IsBool());
}
	assert(ekfObj.HasMember("_obs_buffer_length"));
assert(ekfObj["_obs_buffer_length"].IsUint());
	assert(ekfObj.HasMember("_imu_buffer_length"));
assert(ekfObj["_imu_buffer_length"].IsUint());
	assert(ekfObj.HasMember("_dt_imu_avg"));
assert(ekfObj["_dt_imu_avg"].IsFloat() || ekfObj["_dt_imu_avg"].IsBool());
	assert(ekfObj.HasMember("_dt_ekf_avg"));
assert(ekfObj["_dt_ekf_avg"].IsFloat() || ekfObj["_dt_ekf_avg"].IsBool());
{
	assert(ekfObj["_imu_sample_delayed"].IsObject());
	assert(ekfObj["_imu_sample_delayed"]["time_us"].IsUint64());
	assert(ekfObj["_imu_sample_delayed"]["delta_ang"].IsArray());
	assert(ekfObj["_imu_sample_delayed"]["delta_vel"].IsArray());
	assert(ekfObj["_imu_sample_delayed"]["delta_ang_dt"].IsFloat() || ekfObj["_imu_sample_delayed"]["delta_ang_dt"].IsBool());
	assert(ekfObj["_imu_sample_delayed"]["delta_vel_dt"].IsFloat() || ekfObj["_imu_sample_delayed"]["delta_vel_dt"].IsBool());
	assert(ekfObj["_imu_sample_delayed"]["delta_vel_clipping"].IsArray());
}
{
	assert(ekfObj["_baro_sample_delayed"].IsObject());
	assert(ekfObj["_baro_sample_delayed"]["time_us"].IsUint64());
	assert(ekfObj["_baro_sample_delayed"]["hgt"].IsFloat() || ekfObj["_baro_sample_delayed"]["hgt"].IsBool());
}
{
	assert(ekfObj["_gps_sample_delayed"].IsObject());
	assert(ekfObj["_gps_sample_delayed"]["time_us"].IsUint64());
	assert(ekfObj["_gps_sample_delayed"]["pos"].IsArray());
	assert(ekfObj["_gps_sample_delayed"]["hgt"].IsFloat() || ekfObj["_gps_sample_delayed"]["hgt"].IsBool());
	assert(ekfObj["_gps_sample_delayed"]["vel"].IsArray());
	assert(ekfObj["_gps_sample_delayed"]["yaw"].IsFloat() || ekfObj["_gps_sample_delayed"]["yaw"].IsBool());
	assert(ekfObj["_gps_sample_delayed"]["hacc"].IsFloat() || ekfObj["_gps_sample_delayed"]["hacc"].IsBool());
	assert(ekfObj["_gps_sample_delayed"]["vacc"].IsFloat() || ekfObj["_gps_sample_delayed"]["vacc"].IsBool());
	assert(ekfObj["_gps_sample_delayed"]["sacc"].IsFloat() || ekfObj["_gps_sample_delayed"]["sacc"].IsBool());
}
	{
	assert(ekfObj["_airspeed_sample_delayed"].IsObject());
	assert(ekfObj["_airspeed_sample_delayed"]["time_us"].IsUint64());
	assert(ekfObj["_airspeed_sample_delayed"]["true_airspeed"].IsFloat() || ekfObj["_airspeed_sample_delayed"]["true_airspeed"].IsBool());
	assert(ekfObj["_airspeed_sample_delayed"]["eas2tas"].IsFloat() || ekfObj["_airspeed_sample_delayed"]["eas2tas"].IsBool());
}
{
	assert(ekfObj["_flow_sample_delayed"].IsObject());
	assert(ekfObj["_flow_sample_delayed"]["time_us"].IsUint64());
	assert(ekfObj["_flow_sample_delayed"]["flow_xy_rad"].IsArray());
	assert(ekfObj["_flow_sample_delayed"]["gyro_xyz"].IsArray());
	assert(ekfObj["_flow_sample_delayed"]["dt"].IsFloat() || ekfObj["_flow_sample_delayed"]["dt"].IsBool());
	assert(ekfObj["_flow_sample_delayed"]["quality"].IsUint());
}
{
	assert(ekfObj["_ev_sample_delayed"].IsObject());
	assert(ekfObj["_ev_sample_delayed"]["time_us"].IsUint64());
	assert(ekfObj["_ev_sample_delayed"]["pos"].IsArray());
	assert(ekfObj["_ev_sample_delayed"]["vel"].IsArray());
	assert(ekfObj["_ev_sample_delayed"]["quat"].IsArray());
	assert(ekfObj["_ev_sample_delayed"]["posVar"].IsArray());
	assert(ekfObj["_ev_sample_delayed"]["velCov"].IsArray());
	assert(ekfObj["_ev_sample_delayed"]["angVar"].IsFloat() || ekfObj["_ev_sample_delayed"]["angVar"].IsBool());
	assert(ekfObj["_ev_sample_delayed"]["reset_counter"].IsUint());
}
{
	assert(ekfObj["_ev_sample_delayed_prev"].IsObject());
	assert(ekfObj["_ev_sample_delayed_prev"]["time_us"].IsUint64());
	assert(ekfObj["_ev_sample_delayed_prev"]["pos"].IsArray());
	assert(ekfObj["_ev_sample_delayed_prev"]["vel"].IsArray());
	assert(ekfObj["_ev_sample_delayed_prev"]["quat"].IsArray());
	assert(ekfObj["_ev_sample_delayed_prev"]["posVar"].IsArray());
	assert(ekfObj["_ev_sample_delayed_prev"]["velCov"].IsArray());
	assert(ekfObj["_ev_sample_delayed_prev"]["angVar"].IsFloat() || ekfObj["_ev_sample_delayed_prev"]["angVar"].IsBool());
	assert(ekfObj["_ev_sample_delayed_prev"]["reset_counter"].IsUint());
}
{
	assert(ekfObj["_drag_down_sampled"].IsObject());
	assert(ekfObj["_drag_down_sampled"]["time_us"].IsUint64());
	assert(ekfObj["_drag_down_sampled"]["accelXY"].IsArray());
}
		assert(ekfObj.HasMember("_air_density"));
assert(ekfObj["_air_density"].IsFloat() || ekfObj["_air_density"].IsBool());
	assert(ekfObj.HasMember("_flow_max_rate"));
assert(ekfObj["_flow_max_rate"].IsFloat() || ekfObj["_flow_max_rate"].IsBool());
	assert(ekfObj.HasMember("_flow_min_distance"));
assert(ekfObj["_flow_min_distance"].IsFloat() || ekfObj["_flow_min_distance"].IsBool());
	assert(ekfObj.HasMember("_flow_max_distance"));
assert(ekfObj["_flow_max_distance"].IsFloat() || ekfObj["_flow_max_distance"].IsBool());
{
	assert(ekfObj["_output_new"].IsObject());
	assert(ekfObj["_output_new"]["time_us"].IsUint64());
	assert(ekfObj["_output_new"]["quat_nominal"].IsArray());
	assert(ekfObj["_output_new"]["vel"].IsArray());
	assert(ekfObj["_output_new"]["pos"].IsArray());
}
{
	assert(ekfObj["_output_vert_new"].IsObject());
	assert(ekfObj["_output_vert_new"]["time_us"].IsUint64());
	assert(ekfObj["_output_vert_new"]["vert_vel"].IsFloat() || ekfObj["_output_vert_new"]["vert_vel"].IsBool());
	assert(ekfObj["_output_vert_new"]["vert_vel_integ"].IsFloat() || ekfObj["_output_vert_new"]["vert_vel_integ"].IsBool());
	assert(ekfObj["_output_vert_new"]["dt"].IsFloat() || ekfObj["_output_vert_new"]["dt"].IsBool());
}
{
	assert(ekfObj["_newest_high_rate_imu_sample"].IsObject());
	assert(ekfObj["_newest_high_rate_imu_sample"]["time_us"].IsUint64());
	assert(ekfObj["_newest_high_rate_imu_sample"]["delta_ang"].IsArray());
	assert(ekfObj["_newest_high_rate_imu_sample"]["delta_vel"].IsArray());
	assert(ekfObj["_newest_high_rate_imu_sample"]["delta_ang_dt"].IsFloat() || ekfObj["_newest_high_rate_imu_sample"]["delta_ang_dt"].IsBool());
	assert(ekfObj["_newest_high_rate_imu_sample"]["delta_vel_dt"].IsFloat() || ekfObj["_newest_high_rate_imu_sample"]["delta_vel_dt"].IsBool());
	assert(ekfObj["_newest_high_rate_imu_sample"]["delta_vel_clipping"].IsArray());
}
	assert(ekfObj.HasMember("_R_to_earth_now"));
assert(ekfObj["_R_to_earth_now"].IsArray());
	assert(ekfObj.HasMember("_vel_imu_rel_body_ned"));
assert(ekfObj["_vel_imu_rel_body_ned"].IsArray());
	assert(ekfObj.HasMember("_vel_deriv"));
assert(ekfObj["_vel_deriv"].IsArray());
	assert(ekfObj.HasMember("_imu_updated"));
assert(ekfObj["_imu_updated"].IsBool());
	assert(ekfObj.HasMember("_initialised"));
assert(ekfObj["_initialised"].IsBool());
	assert(ekfObj.HasMember("_NED_origin_initialised"));
assert(ekfObj["_NED_origin_initialised"].IsBool());
	assert(ekfObj.HasMember("_gps_speed_valid"));
assert(ekfObj["_gps_speed_valid"].IsBool());
	assert(ekfObj.HasMember("_gps_origin_eph"));
assert(ekfObj["_gps_origin_eph"].IsFloat() || ekfObj["_gps_origin_eph"].IsBool());
	assert(ekfObj.HasMember("_gps_origin_epv"));
assert(ekfObj["_gps_origin_epv"].IsFloat() || ekfObj["_gps_origin_epv"].IsBool());
{
	assert(ekfObj["_pos_ref"].IsObject());
	assert(ekfObj["_pos_ref"]["_ref_lat"].IsDouble() || ekfObj["_pos_ref"]["_ref_lat"].IsBool());
	assert(ekfObj["_pos_ref"]["_ref_lon"].IsDouble() || ekfObj["_pos_ref"]["_ref_lon"].IsBool());
	assert(ekfObj["_pos_ref"]["_ref_sin_lat"].IsDouble() || ekfObj["_pos_ref"]["_ref_sin_lat"].IsBool());
	assert(ekfObj["_pos_ref"]["_ref_cos_lat"].IsDouble() || ekfObj["_pos_ref"]["_ref_cos_lat"].IsBool());
	assert(ekfObj["_pos_ref"]["_ref_init_done"].IsBool());
}
{
	assert(ekfObj["_gps_pos_prev"].IsObject());
	assert(ekfObj["_gps_pos_prev"]["_ref_lat"].IsDouble() || ekfObj["_gps_pos_prev"]["_ref_lat"].IsBool());
	assert(ekfObj["_gps_pos_prev"]["_ref_lon"].IsDouble() || ekfObj["_gps_pos_prev"]["_ref_lon"].IsBool());
	assert(ekfObj["_gps_pos_prev"]["_ref_sin_lat"].IsDouble() || ekfObj["_gps_pos_prev"]["_ref_sin_lat"].IsBool());
	assert(ekfObj["_gps_pos_prev"]["_ref_cos_lat"].IsDouble() || ekfObj["_gps_pos_prev"]["_ref_cos_lat"].IsBool());
	assert(ekfObj["_gps_pos_prev"]["_ref_init_done"].IsBool());
}
	assert(ekfObj.HasMember("_gps_alt_prev"));
assert(ekfObj["_gps_alt_prev"].IsFloat() || ekfObj["_gps_alt_prev"].IsBool());
	assert(ekfObj.HasMember("_gps_yaw_offset"));
assert(ekfObj["_gps_yaw_offset"].IsFloat() || ekfObj["_gps_yaw_offset"].IsBool());
	assert(ekfObj.HasMember("_yaw_test_ratio"));
assert(ekfObj["_yaw_test_ratio"].IsFloat() || ekfObj["_yaw_test_ratio"].IsBool());
	{
		assert(ekfObj.HasMember("_yaw_signed_test_ratio_lpf"));
		assert(ekfObj["_yaw_signed_test_ratio_lpf"].IsObject());
		assert(ekfObj["_yaw_signed_test_ratio_lpf"].HasMember("_cutoff_freq"));
		assert(ekfObj["_yaw_signed_test_ratio_lpf"]["_cutoff_freq"].IsFloat());
		assert(ekfObj["_yaw_signed_test_ratio_lpf"].HasMember("_alpha"));
		assert(ekfObj["_yaw_signed_test_ratio_lpf"]["_alpha"].IsFloat());
		assert(ekfObj["_yaw_signed_test_ratio_lpf"].HasMember("_filter_state"));
		assert(ekfObj["_yaw_signed_test_ratio_lpf"]["_filter_state"].IsFloat());
	}
	assert(ekfObj.HasMember("_mag_test_ratio"));
assert(ekfObj["_mag_test_ratio"].IsArray());
	assert(ekfObj.HasMember("_gps_vel_test_ratio"));
assert(ekfObj["_gps_vel_test_ratio"].IsArray());
	assert(ekfObj.HasMember("_gps_pos_test_ratio"));
assert(ekfObj["_gps_pos_test_ratio"].IsArray());
	assert(ekfObj.HasMember("_ev_vel_test_ratio"));
assert(ekfObj["_ev_vel_test_ratio"].IsArray());
	assert(ekfObj.HasMember("_ev_pos_test_ratio"));
assert(ekfObj["_ev_pos_test_ratio"].IsArray());
	assert(ekfObj.HasMember("_aux_vel_test_ratio"));
assert(ekfObj["_aux_vel_test_ratio"].IsArray());
	assert(ekfObj.HasMember("_baro_hgt_test_ratio"));
assert(ekfObj["_baro_hgt_test_ratio"].IsFloat() || ekfObj["_baro_hgt_test_ratio"].IsBool());
	assert(ekfObj.HasMember("_rng_hgt_test_ratio"));
assert(ekfObj["_rng_hgt_test_ratio"].IsFloat() || ekfObj["_rng_hgt_test_ratio"].IsBool());
	assert(ekfObj.HasMember("_optflow_test_ratio"));
assert(ekfObj["_optflow_test_ratio"].IsFloat() || ekfObj["_optflow_test_ratio"].IsBool());
	assert(ekfObj.HasMember("_tas_test_ratio"));
assert(ekfObj["_tas_test_ratio"].IsFloat() || ekfObj["_tas_test_ratio"].IsBool());
	assert(ekfObj.HasMember("_hagl_test_ratio"));
assert(ekfObj["_hagl_test_ratio"].IsFloat() || ekfObj["_hagl_test_ratio"].IsBool());
	assert(ekfObj.HasMember("_beta_test_ratio"));
assert(ekfObj["_beta_test_ratio"].IsFloat() || ekfObj["_beta_test_ratio"].IsBool());
	assert(ekfObj.HasMember("_drag_test_ratio"));
assert(ekfObj["_drag_test_ratio"].IsArray());
	{
		assert(ekfObj["_innov_check_fail_status"].IsObject());
		assert(ekfObj["_innov_check_fail_status"]["flags"].IsObject());
		assert(ekfObj["_innov_check_fail_status"]["flags"]["reject_airspeed"].IsBool());
		assert(ekfObj["_innov_check_fail_status"]["flags"]["reject_hagl"].IsBool());
		assert(ekfObj["_innov_check_fail_status"]["flags"]["reject_hor_pos"].IsBool());
		assert(ekfObj["_innov_check_fail_status"]["flags"]["reject_hor_vel"].IsBool());
		assert(ekfObj["_innov_check_fail_status"]["flags"]["reject_mag_x"].IsBool());
		assert(ekfObj["_innov_check_fail_status"]["flags"]["reject_mag_y"].IsBool());
		assert(ekfObj["_innov_check_fail_status"]["flags"]["reject_mag_z"].IsBool());
		assert(ekfObj["_innov_check_fail_status"]["flags"]["reject_optflow_X"].IsBool());
		assert(ekfObj["_innov_check_fail_status"]["flags"]["reject_optflow_Y"].IsBool());
		assert(ekfObj["_innov_check_fail_status"]["flags"]["reject_sideslip"].IsBool());
		assert(ekfObj["_innov_check_fail_status"]["flags"]["reject_ver_pos"].IsBool());
		assert(ekfObj["_innov_check_fail_status"]["flags"]["reject_ver_vel"].IsBool());
		assert(ekfObj["_innov_check_fail_status"]["flags"]["reject_yaw"].IsBool());
	}
	assert(ekfObj.HasMember("_deadreckon_time_exceeded"));
assert(ekfObj["_deadreckon_time_exceeded"].IsBool());
	assert(ekfObj.HasMember("_gps_horizontal_position_drift_rate_m_s"));
assert(ekfObj["_gps_horizontal_position_drift_rate_m_s"].IsFloat() || ekfObj["_gps_horizontal_position_drift_rate_m_s"].IsBool());
	assert(ekfObj.HasMember("_gps_vertical_position_drift_rate_m_s"));
assert(ekfObj["_gps_vertical_position_drift_rate_m_s"].IsFloat() || ekfObj["_gps_vertical_position_drift_rate_m_s"].IsBool());
	assert(ekfObj.HasMember("_gps_filtered_horizontal_velocity_m_s"));
assert(ekfObj["_gps_filtered_horizontal_velocity_m_s"].IsFloat() || ekfObj["_gps_filtered_horizontal_velocity_m_s"].IsBool());
	assert(ekfObj.HasMember("_time_last_on_ground_us"));
assert(ekfObj["_time_last_on_ground_us"].IsUint64());
	assert(ekfObj.HasMember("_time_last_in_air"));
assert(ekfObj["_time_last_in_air"].IsUint64());
	if(ekfObj.HasMember("_imu_buffer")){		rapidjson::Value & imuSample_buffer = ekfObj["_imu_buffer"];
		assert(imuSample_buffer["_size"].IsUint());
		assert(imuSample_buffer["_head"].IsUint());
		assert(imuSample_buffer["_tail"].IsUint());
		assert(imuSample_buffer["_first_write"].IsBool());
		assert(imuSample_buffer["_buffer"].IsArray());
		auto & array = imuSample_buffer["_buffer"];
		for(unsigned int index = 0; index < array.Size(); index++){
			assert(imuSample_buffer["_buffer"][index].IsObject());
			assert(imuSample_buffer["_buffer"][index]["time_us"].IsUint64());
			assert(imuSample_buffer["_buffer"][index]["delta_ang"].IsArray());
			assert(imuSample_buffer["_buffer"][index]["delta_vel"].IsArray());
			assert(imuSample_buffer["_buffer"][index]["delta_ang_dt"].IsFloat() || imuSample_buffer["_buffer"][index]["delta_ang_dt"].IsBool());
			assert(imuSample_buffer["_buffer"][index]["delta_vel_dt"].IsFloat() || imuSample_buffer["_buffer"][index]["delta_vel_dt"].IsBool());
			assert(imuSample_buffer["_buffer"][index]["delta_vel_clipping"].IsArray());
		}	}	if(ekfObj.HasMember("_output_buffer")){		rapidjson::Value & outputSample_buffer = ekfObj["_output_buffer"];
		assert(outputSample_buffer["_size"].IsUint());
		assert(outputSample_buffer["_head"].IsUint());
		assert(outputSample_buffer["_tail"].IsUint());
		assert(outputSample_buffer["_first_write"].IsBool());
		assert(outputSample_buffer["_buffer"].IsArray());
		auto & array = outputSample_buffer["_buffer"];
		for(unsigned int index = 0; index < array.Size(); index++){
			assert(outputSample_buffer["_buffer"][index].IsObject());
			assert(outputSample_buffer["_buffer"][index]["time_us"].IsUint64());
			assert(outputSample_buffer["_buffer"][index]["quat_nominal"].IsArray());
			assert(outputSample_buffer["_buffer"][index]["vel"].IsArray());
			assert(outputSample_buffer["_buffer"][index]["pos"].IsArray());
		}	}	if(ekfObj.HasMember("_output_vert_buffer")){		rapidjson::Value & outputVert_buffer = ekfObj["_output_vert_buffer"];
		assert(outputVert_buffer["_size"].IsUint());
		assert(outputVert_buffer["_head"].IsUint());
		assert(outputVert_buffer["_tail"].IsUint());
		assert(outputVert_buffer["_first_write"].IsBool());
		assert(outputVert_buffer["_buffer"].IsArray());
		auto & array = outputVert_buffer["_buffer"];
		for(unsigned int index = 0; index < array.Size(); index++){
			assert(outputVert_buffer["_buffer"][index].IsObject());
			assert(outputVert_buffer["_buffer"][index]["time_us"].IsUint64());
			assert(outputVert_buffer["_buffer"][index]["vert_vel"].IsFloat() || outputVert_buffer["_buffer"][index]["vert_vel"].IsBool());
			assert(outputVert_buffer["_buffer"][index]["vert_vel_integ"].IsFloat() || outputVert_buffer["_buffer"][index]["vert_vel_integ"].IsBool());
			assert(outputVert_buffer["_buffer"][index]["dt"].IsFloat() || outputVert_buffer["_buffer"][index]["dt"].IsBool());
		}	}	if(ekfObj.HasMember("_gps_buffer")){		rapidjson::Value & gpsSample_buffer = ekfObj["_gps_buffer"];
		assert(gpsSample_buffer["_size"].IsUint());
		assert(gpsSample_buffer["_head"].IsUint());
		assert(gpsSample_buffer["_tail"].IsUint());
		assert(gpsSample_buffer["_first_write"].IsBool());
		assert(gpsSample_buffer["_buffer"].IsArray());
		auto & array = gpsSample_buffer["_buffer"];
		for(unsigned int index = 0; index < array.Size(); index++){
			assert(gpsSample_buffer["_buffer"][index].IsObject());
			assert(gpsSample_buffer["_buffer"][index]["time_us"].IsUint64());
			assert(gpsSample_buffer["_buffer"][index]["pos"].IsArray());
			assert(gpsSample_buffer["_buffer"][index]["hgt"].IsFloat() || gpsSample_buffer["_buffer"][index]["hgt"].IsBool());
			assert(gpsSample_buffer["_buffer"][index]["vel"].IsArray());
			assert(gpsSample_buffer["_buffer"][index]["yaw"].IsFloat() || gpsSample_buffer["_buffer"][index]["yaw"].IsBool());
			assert(gpsSample_buffer["_buffer"][index]["hacc"].IsFloat() || gpsSample_buffer["_buffer"][index]["hacc"].IsBool());
			assert(gpsSample_buffer["_buffer"][index]["vacc"].IsFloat() || gpsSample_buffer["_buffer"][index]["vacc"].IsBool());
			assert(gpsSample_buffer["_buffer"][index]["sacc"].IsFloat() || gpsSample_buffer["_buffer"][index]["sacc"].IsBool());
		}	}	if(ekfObj.HasMember("_mag_buffer")){		rapidjson::Value & magSample_buffer = ekfObj["_mag_buffer"];
		assert(magSample_buffer["_size"].IsUint());
		assert(magSample_buffer["_head"].IsUint());
		assert(magSample_buffer["_tail"].IsUint());
		assert(magSample_buffer["_first_write"].IsBool());
		assert(magSample_buffer["_buffer"].IsArray());
		auto & array = magSample_buffer["_buffer"];
		for(unsigned int index = 0; index < array.Size(); index++){
			assert(magSample_buffer["_buffer"][index].IsObject());
			assert(magSample_buffer["_buffer"][index]["time_us"].IsUint64());
			assert(magSample_buffer["_buffer"][index]["mag"].IsArray());
		}	}	if(ekfObj.HasMember("_baro_buffer")){		rapidjson::Value & baroSample_buffer = ekfObj["_baro_buffer"];
		assert(baroSample_buffer["_size"].IsUint());
		assert(baroSample_buffer["_head"].IsUint());
		assert(baroSample_buffer["_tail"].IsUint());
		assert(baroSample_buffer["_first_write"].IsBool());
		assert(baroSample_buffer["_buffer"].IsArray());
		auto & array = baroSample_buffer["_buffer"];
		for(unsigned int index = 0; index < array.Size(); index++){
			assert(baroSample_buffer["_buffer"][index].IsObject());
			assert(baroSample_buffer["_buffer"][index]["time_us"].IsUint64());
			assert(baroSample_buffer["_buffer"][index]["hgt"].IsFloat() || baroSample_buffer["_buffer"][index]["hgt"].IsBool());
		}	}	if(ekfObj.HasMember("_range_buffer")){		rapidjson::Value & rangeSample_buffer = ekfObj["_range_buffer"];
		assert(rangeSample_buffer["_size"].IsUint());
		assert(rangeSample_buffer["_head"].IsUint());
		assert(rangeSample_buffer["_tail"].IsUint());
		assert(rangeSample_buffer["_first_write"].IsBool());
		assert(rangeSample_buffer["_buffer"].IsArray());
		auto & array = rangeSample_buffer["_buffer"];
		for(unsigned int index = 0; index < array.Size(); index++){
			assert(rangeSample_buffer["_buffer"][index].IsObject());
			assert(rangeSample_buffer["_buffer"][index]["time_us"].IsUint64());
			assert(rangeSample_buffer["_buffer"][index]["rng"].IsFloat() || rangeSample_buffer["_buffer"][index]["rng"].IsBool());
		}	}	if(ekfObj.HasMember("_airspeed_buffer")){		rapidjson::Value & airspeedSample_buffer = ekfObj["_airspeed_buffer"];
		assert(airspeedSample_buffer["_size"].IsUint());
		assert(airspeedSample_buffer["_head"].IsUint());
		assert(airspeedSample_buffer["_tail"].IsUint());
		assert(airspeedSample_buffer["_first_write"].IsBool());
		assert(airspeedSample_buffer["_buffer"].IsArray());
		auto & array = airspeedSample_buffer["_buffer"];
		for(unsigned int index = 0; index < array.Size(); index++){
			assert(airspeedSample_buffer["_buffer"][index].IsObject());
			assert(airspeedSample_buffer["_buffer"][index]["time_us"].IsUint64());
			assert(airspeedSample_buffer["_buffer"][index]["true_airspeed"].IsFloat() || airspeedSample_buffer["_buffer"][index]["true_airspeed"].IsBool());
			assert(airspeedSample_buffer["_buffer"][index]["eas2tas"].IsFloat() || airspeedSample_buffer["_buffer"][index]["eas2tas"].IsBool());
		}	}	if(ekfObj.HasMember("_flow_buffer")){		rapidjson::Value & flowSample_buffer = ekfObj["_flow_buffer"];
		assert(flowSample_buffer["_size"].IsUint());
		assert(flowSample_buffer["_head"].IsUint());
		assert(flowSample_buffer["_tail"].IsUint());
		assert(flowSample_buffer["_first_write"].IsBool());
		assert(flowSample_buffer["_buffer"].IsArray());
		auto & array = flowSample_buffer["_buffer"];
		for(unsigned int index = 0; index < array.Size(); index++){
			assert(flowSample_buffer["_buffer"][index].IsObject());
			assert(flowSample_buffer["_buffer"][index]["time_us"].IsUint64());
			assert(flowSample_buffer["_buffer"][index]["flow_xy_rad"].IsArray());
			assert(flowSample_buffer["_buffer"][index]["gyro_xyz"].IsArray());
			assert(flowSample_buffer["_buffer"][index]["dt"].IsFloat() || flowSample_buffer["_buffer"][index]["dt"].IsBool());
			assert(flowSample_buffer["_buffer"][index]["quality"].IsUint());
		}	}	if(ekfObj.HasMember("_ext_vision_buffer")){		rapidjson::Value & extVisionSample_buffer = ekfObj["_ext_vision_buffer"];
		assert(extVisionSample_buffer["_size"].IsUint());
		assert(extVisionSample_buffer["_head"].IsUint());
		assert(extVisionSample_buffer["_tail"].IsUint());
		assert(extVisionSample_buffer["_first_write"].IsBool());
		assert(extVisionSample_buffer["_buffer"].IsArray());
		auto & array = extVisionSample_buffer["_buffer"];
		for(unsigned int index = 0; index < array.Size(); index++){
			assert(extVisionSample_buffer["_buffer"][index].IsObject());
			assert(extVisionSample_buffer["_buffer"][index]["time_us"].IsUint64());
			assert(extVisionSample_buffer["_buffer"][index]["pos"].IsArray());
			assert(extVisionSample_buffer["_buffer"][index]["vel"].IsArray());
			assert(extVisionSample_buffer["_buffer"][index]["quat"].IsArray());
			assert(extVisionSample_buffer["_buffer"][index]["posVar"].IsArray());
			assert(extVisionSample_buffer["_buffer"][index]["velCov"].IsArray());
			assert(extVisionSample_buffer["_buffer"][index]["angVar"].IsFloat() || extVisionSample_buffer["_buffer"][index]["angVar"].IsBool());
			assert(extVisionSample_buffer["_buffer"][index]["reset_counter"].IsUint());
		}	}	if(ekfObj.HasMember("_drag_buffer")){		rapidjson::Value & dragSample_buffer = ekfObj["_drag_buffer"];
		assert(dragSample_buffer["_size"].IsUint());
		assert(dragSample_buffer["_head"].IsUint());
		assert(dragSample_buffer["_tail"].IsUint());
		assert(dragSample_buffer["_first_write"].IsBool());
		assert(dragSample_buffer["_buffer"].IsArray());
		auto & array = dragSample_buffer["_buffer"];
		for(unsigned int index = 0; index < array.Size(); index++){
			assert(dragSample_buffer["_buffer"][index].IsObject());
			assert(dragSample_buffer["_buffer"][index]["time_us"].IsUint64());
			assert(dragSample_buffer["_buffer"][index]["accelXY"].IsArray());
		}	}	if(ekfObj.HasMember("_auxvel_buffer")){		rapidjson::Value & auxVelSample_buffer = ekfObj["_auxvel_buffer"];
		assert(auxVelSample_buffer["_size"].IsUint());
		assert(auxVelSample_buffer["_head"].IsUint());
		assert(auxVelSample_buffer["_tail"].IsUint());
		assert(auxVelSample_buffer["_first_write"].IsBool());
		assert(auxVelSample_buffer["_buffer"].IsArray());
		auto & array = auxVelSample_buffer["_buffer"];
		for(unsigned int index = 0; index < array.Size(); index++){
			assert(auxVelSample_buffer["_buffer"][index].IsObject());
			assert(auxVelSample_buffer["_buffer"][index]["time_us"].IsUint64());
			assert(auxVelSample_buffer["_buffer"][index]["vel"].IsArray());
			assert(auxVelSample_buffer["_buffer"][index]["velVar"].IsArray());
		}	}	assert(ekfObj.HasMember("_time_last_imu"));
assert(ekfObj["_time_last_imu"].IsUint64());
	assert(ekfObj.HasMember("_time_last_gps"));
assert(ekfObj["_time_last_gps"].IsUint64());
	assert(ekfObj.HasMember("_time_last_mag"));
assert(ekfObj["_time_last_mag"].IsUint64());
	assert(ekfObj.HasMember("_time_last_baro"));
assert(ekfObj["_time_last_baro"].IsUint64());
	assert(ekfObj.HasMember("_time_last_range"));
assert(ekfObj["_time_last_range"].IsUint64());
	assert(ekfObj.HasMember("_time_last_airspeed"));
assert(ekfObj["_time_last_airspeed"].IsUint64());
	assert(ekfObj.HasMember("_time_last_ext_vision"));
assert(ekfObj["_time_last_ext_vision"].IsUint64());
	assert(ekfObj.HasMember("_time_last_optflow"));
assert(ekfObj["_time_last_optflow"].IsUint64());
	assert(ekfObj.HasMember("_time_last_auxvel"));
assert(ekfObj["_time_last_auxvel"].IsUint64());
	assert(ekfObj.HasMember("_time_last_gnd_effect_on"));
assert(ekfObj["_time_last_gnd_effect_on"].IsUint64());
	{
		assert(ekfObj["_fault_status"].IsObject());
		assert(ekfObj["_fault_status"]["flags"].IsObject());
		assert(ekfObj["_fault_status"]["flags"]["bad_acc_bias"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_acc_clipping"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_acc_vertical"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_airspeed"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_hdg"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_mag_decl"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_mag_x"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_mag_y"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_mag_z"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_optflow_X"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_optflow_Y"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_pos_D"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_pos_E"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_pos_N"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_sideslip"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_vel_D"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_vel_E"].IsBool());
		assert(ekfObj["_fault_status"]["flags"]["bad_vel_N"].IsBool());
	}
	assert(ekfObj.HasMember("_mag_declination_gps"));
assert(ekfObj["_mag_declination_gps"].IsFloat() || ekfObj["_mag_declination_gps"].IsBool());
	assert(ekfObj.HasMember("_mag_inclination_gps"));
assert(ekfObj["_mag_inclination_gps"].IsFloat() || ekfObj["_mag_inclination_gps"].IsBool());
	assert(ekfObj.HasMember("_mag_strength_gps"));
assert(ekfObj["_mag_strength_gps"].IsFloat() || ekfObj["_mag_strength_gps"].IsBool());
	{
		assert(ekfObj["_control_status"].IsObject());
		assert(ekfObj["_control_status"]["flags"].IsObject());
		assert(ekfObj["_control_status"]["flags"]["baro_hgt"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["ev_hgt"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["ev_pos"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["ev_vel"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["ev_yaw"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["fixed_wing"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["fuse_aspd"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["fuse_beta"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["gnd_effect"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["gps"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["gps_hgt"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["gps_yaw"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["gps_yaw_fault"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["in_air"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["inertial_dead_reckoning"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["mag_3D"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["mag_aligned_in_flight"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["mag_dec"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["mag_fault"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["mag_field_disturbed"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["mag_hdg"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["opt_flow"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["rng_fault"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["rng_hgt"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["rng_kin_consistent"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["rng_stuck"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["synthetic_mag_z"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["tilt_align"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["vehicle_at_rest"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["wind"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["wind_dead_reckoning"].IsBool());
		assert(ekfObj["_control_status"]["flags"]["yaw_align"].IsBool());
	}
	{
		assert(ekfObj["_control_status_prev"].IsObject());
		assert(ekfObj["_control_status_prev"]["flags"].IsObject());
		assert(ekfObj["_control_status_prev"]["flags"]["baro_hgt"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["ev_hgt"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["ev_pos"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["ev_vel"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["ev_yaw"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["fixed_wing"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["fuse_aspd"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["fuse_beta"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["gnd_effect"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["gps"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["gps_hgt"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["gps_yaw"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["gps_yaw_fault"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["in_air"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["inertial_dead_reckoning"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["mag_3D"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["mag_aligned_in_flight"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["mag_dec"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["mag_fault"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["mag_field_disturbed"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["mag_hdg"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["opt_flow"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["rng_fault"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["rng_hgt"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["rng_kin_consistent"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["rng_stuck"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["synthetic_mag_z"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["tilt_align"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["vehicle_at_rest"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["wind"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["wind_dead_reckoning"].IsBool());
		assert(ekfObj["_control_status_prev"]["flags"]["yaw_align"].IsBool());
	}
	{
		assert(ekfObj["_warning_events"].IsObject());
		assert(ekfObj["_warning_events"]["flags"].IsObject());
		assert(ekfObj["_warning_events"]["flags"]["bad_yaw_using_gps_course"].IsBool());
		assert(ekfObj["_warning_events"]["flags"]["emergency_yaw_reset_gps_yaw_stopped"].IsBool());
		assert(ekfObj["_warning_events"]["flags"]["emergency_yaw_reset_mag_stopped"].IsBool());
		assert(ekfObj["_warning_events"]["flags"]["gps_data_stopped"].IsBool());
		assert(ekfObj["_warning_events"]["flags"]["gps_data_stopped_using_alternate"].IsBool());
		assert(ekfObj["_warning_events"]["flags"]["gps_fusion_timout"].IsBool());
		assert(ekfObj["_warning_events"]["flags"]["gps_quality_poor"].IsBool());
		assert(ekfObj["_warning_events"]["flags"]["height_sensor_timeout"].IsBool());
		assert(ekfObj["_warning_events"]["flags"]["invalid_accel_bias_cov_reset"].IsBool());
		assert(ekfObj["_warning_events"]["flags"]["stopping_mag_use"].IsBool());
		assert(ekfObj["_warning_events"]["flags"]["stopping_navigation"].IsBool());
		assert(ekfObj["_warning_events"]["flags"]["vision_data_stopped"].IsBool());
	}
	{
		assert(ekfObj["_information_events"].IsObject());
		assert(ekfObj["_information_events"]["flags"].IsObject());
		assert(ekfObj["_information_events"]["flags"]["gps_checks_passed"].IsBool());
		assert(ekfObj["_information_events"]["flags"]["reset_pos_to_gps"].IsBool());
		assert(ekfObj["_information_events"]["flags"]["reset_pos_to_last_known"].IsBool());
		assert(ekfObj["_information_events"]["flags"]["reset_pos_to_vision"].IsBool());
		assert(ekfObj["_information_events"]["flags"]["reset_vel_to_flow"].IsBool());
		assert(ekfObj["_information_events"]["flags"]["reset_vel_to_gps"].IsBool());
		assert(ekfObj["_information_events"]["flags"]["reset_vel_to_vision"].IsBool());
		assert(ekfObj["_information_events"]["flags"]["reset_vel_to_zero"].IsBool());
		assert(ekfObj["_information_events"]["flags"]["starting_gps_fusion"].IsBool());
		assert(ekfObj["_information_events"]["flags"]["starting_vision_pos_fusion"].IsBool());
		assert(ekfObj["_information_events"]["flags"]["starting_vision_vel_fusion"].IsBool());
		assert(ekfObj["_information_events"]["flags"]["starting_vision_yaw_fusion"].IsBool());
		assert(ekfObj["_information_events"]["flags"]["yaw_aligned_to_imu_gps"].IsBool());
	}
		assert(ekfObj.HasMember("_min_obs_interval_us"));
assert(ekfObj["_min_obs_interval_us"].IsUint());
	assert(ekfObj.HasMember("_drag_sample_count"));
assert(ekfObj["_drag_sample_count"].IsUint());
	assert(ekfObj.HasMember("_drag_sample_time_dt"));
assert(ekfObj["_drag_sample_time_dt"].IsFloat() || ekfObj["_drag_sample_time_dt"].IsBool());

}
void EstimatorInterface::loadFromJson(rapidjson::Value & ekfObj){
{
	rapidjson::Value& structObj = ekfObj["_params"];
			_params.filter_update_interval_us = structObj["filter_update_interval_us"].GetInt();
			_params.fusion_mode = structObj["fusion_mode"].GetInt();
			_params.vdist_sensor_type = structObj["vdist_sensor_type"].GetInt();
			_params.terrain_fusion_mode = structObj["terrain_fusion_mode"].GetInt();
			_params.sensor_interval_max_ms = structObj["sensor_interval_max_ms"].GetInt();
		if (structObj["mag_delay_ms"].IsBool()){
			_params.mag_delay_ms = NAN;
		}else{
			_params.mag_delay_ms = structObj["mag_delay_ms"].GetFloat();
		}
		if (structObj["baro_delay_ms"].IsBool()){
			_params.baro_delay_ms = NAN;
		}else{
			_params.baro_delay_ms = structObj["baro_delay_ms"].GetFloat();
		}
		if (structObj["gps_delay_ms"].IsBool()){
			_params.gps_delay_ms = NAN;
		}else{
			_params.gps_delay_ms = structObj["gps_delay_ms"].GetFloat();
		}
		if (structObj["airspeed_delay_ms"].IsBool()){
			_params.airspeed_delay_ms = NAN;
		}else{
			_params.airspeed_delay_ms = structObj["airspeed_delay_ms"].GetFloat();
		}
		if (structObj["flow_delay_ms"].IsBool()){
			_params.flow_delay_ms = NAN;
		}else{
			_params.flow_delay_ms = structObj["flow_delay_ms"].GetFloat();
		}
		if (structObj["range_delay_ms"].IsBool()){
			_params.range_delay_ms = NAN;
		}else{
			_params.range_delay_ms = structObj["range_delay_ms"].GetFloat();
		}
		if (structObj["ev_delay_ms"].IsBool()){
			_params.ev_delay_ms = NAN;
		}else{
			_params.ev_delay_ms = structObj["ev_delay_ms"].GetFloat();
		}
		if (structObj["auxvel_delay_ms"].IsBool()){
			_params.auxvel_delay_ms = NAN;
		}else{
			_params.auxvel_delay_ms = structObj["auxvel_delay_ms"].GetFloat();
		}
		if (structObj["gyro_noise"].IsBool()){
			_params.gyro_noise = NAN;
		}else{
			_params.gyro_noise = structObj["gyro_noise"].GetFloat();
		}
		if (structObj["accel_noise"].IsBool()){
			_params.accel_noise = NAN;
		}else{
			_params.accel_noise = structObj["accel_noise"].GetFloat();
		}
		if (structObj["gyro_bias_p_noise"].IsBool()){
			_params.gyro_bias_p_noise = NAN;
		}else{
			_params.gyro_bias_p_noise = structObj["gyro_bias_p_noise"].GetFloat();
		}
		if (structObj["accel_bias_p_noise"].IsBool()){
			_params.accel_bias_p_noise = NAN;
		}else{
			_params.accel_bias_p_noise = structObj["accel_bias_p_noise"].GetFloat();
		}
		if (structObj["mage_p_noise"].IsBool()){
			_params.mage_p_noise = NAN;
		}else{
			_params.mage_p_noise = structObj["mage_p_noise"].GetFloat();
		}
		if (structObj["magb_p_noise"].IsBool()){
			_params.magb_p_noise = NAN;
		}else{
			_params.magb_p_noise = structObj["magb_p_noise"].GetFloat();
		}
		if (structObj["wind_vel_p_noise"].IsBool()){
			_params.wind_vel_p_noise = NAN;
		}else{
			_params.wind_vel_p_noise = structObj["wind_vel_p_noise"].GetFloat();
		}
		if (structObj["terrain_p_noise"].IsBool()){
			_params.terrain_p_noise = NAN;
		}else{
			_params.terrain_p_noise = structObj["terrain_p_noise"].GetFloat();
		}
		if (structObj["terrain_gradient"].IsBool()){
			_params.terrain_gradient = NAN;
		}else{
			_params.terrain_gradient = structObj["terrain_gradient"].GetFloat();
		}
		if (structObj["switch_on_gyro_bias"].IsBool()){
			_params.switch_on_gyro_bias = NAN;
		}else{
			_params.switch_on_gyro_bias = structObj["switch_on_gyro_bias"].GetFloat();
		}
		if (structObj["switch_on_accel_bias"].IsBool()){
			_params.switch_on_accel_bias = NAN;
		}else{
			_params.switch_on_accel_bias = structObj["switch_on_accel_bias"].GetFloat();
		}
		if (structObj["initial_tilt_err"].IsBool()){
			_params.initial_tilt_err = NAN;
		}else{
			_params.initial_tilt_err = structObj["initial_tilt_err"].GetFloat();
		}
		if (structObj["gps_vel_noise"].IsBool()){
			_params.gps_vel_noise = NAN;
		}else{
			_params.gps_vel_noise = structObj["gps_vel_noise"].GetFloat();
		}
		if (structObj["gps_pos_noise"].IsBool()){
			_params.gps_pos_noise = NAN;
		}else{
			_params.gps_pos_noise = structObj["gps_pos_noise"].GetFloat();
		}
		if (structObj["pos_noaid_noise"].IsBool()){
			_params.pos_noaid_noise = NAN;
		}else{
			_params.pos_noaid_noise = structObj["pos_noaid_noise"].GetFloat();
		}
		if (structObj["baro_noise"].IsBool()){
			_params.baro_noise = NAN;
		}else{
			_params.baro_noise = structObj["baro_noise"].GetFloat();
		}
		if (structObj["baro_drift_rate"].IsBool()){
			_params.baro_drift_rate = NAN;
		}else{
			_params.baro_drift_rate = structObj["baro_drift_rate"].GetFloat();
		}
		if (structObj["baro_innov_gate"].IsBool()){
			_params.baro_innov_gate = NAN;
		}else{
			_params.baro_innov_gate = structObj["baro_innov_gate"].GetFloat();
		}
		if (structObj["gps_pos_innov_gate"].IsBool()){
			_params.gps_pos_innov_gate = NAN;
		}else{
			_params.gps_pos_innov_gate = structObj["gps_pos_innov_gate"].GetFloat();
		}
		if (structObj["gps_vel_innov_gate"].IsBool()){
			_params.gps_vel_innov_gate = NAN;
		}else{
			_params.gps_vel_innov_gate = structObj["gps_vel_innov_gate"].GetFloat();
		}
		if (structObj["gnd_effect_deadzone"].IsBool()){
			_params.gnd_effect_deadzone = NAN;
		}else{
			_params.gnd_effect_deadzone = structObj["gnd_effect_deadzone"].GetFloat();
		}
		if (structObj["gnd_effect_max_hgt"].IsBool()){
			_params.gnd_effect_max_hgt = NAN;
		}else{
			_params.gnd_effect_max_hgt = structObj["gnd_effect_max_hgt"].GetFloat();
		}
		if (structObj["mag_heading_noise"].IsBool()){
			_params.mag_heading_noise = NAN;
		}else{
			_params.mag_heading_noise = structObj["mag_heading_noise"].GetFloat();
		}
		if (structObj["mag_noise"].IsBool()){
			_params.mag_noise = NAN;
		}else{
			_params.mag_noise = structObj["mag_noise"].GetFloat();
		}
		if (structObj["mag_declination_deg"].IsBool()){
			_params.mag_declination_deg = NAN;
		}else{
			_params.mag_declination_deg = structObj["mag_declination_deg"].GetFloat();
		}
		if (structObj["heading_innov_gate"].IsBool()){
			_params.heading_innov_gate = NAN;
		}else{
			_params.heading_innov_gate = structObj["heading_innov_gate"].GetFloat();
		}
		if (structObj["mag_innov_gate"].IsBool()){
			_params.mag_innov_gate = NAN;
		}else{
			_params.mag_innov_gate = structObj["mag_innov_gate"].GetFloat();
		}
			_params.mag_declination_source = structObj["mag_declination_source"].GetInt();
			_params.mag_fusion_type = structObj["mag_fusion_type"].GetInt();
		if (structObj["mag_acc_gate"].IsBool()){
			_params.mag_acc_gate = NAN;
		}else{
			_params.mag_acc_gate = structObj["mag_acc_gate"].GetFloat();
		}
		if (structObj["mag_yaw_rate_gate"].IsBool()){
			_params.mag_yaw_rate_gate = NAN;
		}else{
			_params.mag_yaw_rate_gate = structObj["mag_yaw_rate_gate"].GetFloat();
		}
		if (structObj["gps_heading_noise"].IsBool()){
			_params.gps_heading_noise = NAN;
		}else{
			_params.gps_heading_noise = structObj["gps_heading_noise"].GetFloat();
		}
		if (structObj["tas_innov_gate"].IsBool()){
			_params.tas_innov_gate = NAN;
		}else{
			_params.tas_innov_gate = structObj["tas_innov_gate"].GetFloat();
		}
		if (structObj["eas_noise"].IsBool()){
			_params.eas_noise = NAN;
		}else{
			_params.eas_noise = structObj["eas_noise"].GetFloat();
		}
		if (structObj["arsp_thr"].IsBool()){
			_params.arsp_thr = NAN;
		}else{
			_params.arsp_thr = structObj["arsp_thr"].GetFloat();
		}
		if (structObj["beta_innov_gate"].IsBool()){
			_params.beta_innov_gate = NAN;
		}else{
			_params.beta_innov_gate = structObj["beta_innov_gate"].GetFloat();
		}
		if (structObj["beta_noise"].IsBool()){
			_params.beta_noise = NAN;
		}else{
			_params.beta_noise = structObj["beta_noise"].GetFloat();
		}
		if (structObj["range_noise"].IsBool()){
			_params.range_noise = NAN;
		}else{
			_params.range_noise = structObj["range_noise"].GetFloat();
		}
		if (structObj["range_innov_gate"].IsBool()){
			_params.range_innov_gate = NAN;
		}else{
			_params.range_innov_gate = structObj["range_innov_gate"].GetFloat();
		}
		if (structObj["rng_gnd_clearance"].IsBool()){
			_params.rng_gnd_clearance = NAN;
		}else{
			_params.rng_gnd_clearance = structObj["rng_gnd_clearance"].GetFloat();
		}
		if (structObj["rng_sens_pitch"].IsBool()){
			_params.rng_sens_pitch = NAN;
		}else{
			_params.rng_sens_pitch = structObj["rng_sens_pitch"].GetFloat();
		}
		if (structObj["range_noise_scaler"].IsBool()){
			_params.range_noise_scaler = NAN;
		}else{
			_params.range_noise_scaler = structObj["range_noise_scaler"].GetFloat();
		}
		if (structObj["max_hagl_for_range_aid"].IsBool()){
			_params.max_hagl_for_range_aid = NAN;
		}else{
			_params.max_hagl_for_range_aid = structObj["max_hagl_for_range_aid"].GetFloat();
		}
		if (structObj["max_vel_for_range_aid"].IsBool()){
			_params.max_vel_for_range_aid = NAN;
		}else{
			_params.max_vel_for_range_aid = structObj["max_vel_for_range_aid"].GetFloat();
		}
			_params.range_aid = structObj["range_aid"].GetInt();
		if (structObj["range_aid_innov_gate"].IsBool()){
			_params.range_aid_innov_gate = NAN;
		}else{
			_params.range_aid_innov_gate = structObj["range_aid_innov_gate"].GetFloat();
		}
		if (structObj["range_valid_quality_s"].IsBool()){
			_params.range_valid_quality_s = NAN;
		}else{
			_params.range_valid_quality_s = structObj["range_valid_quality_s"].GetFloat();
		}
		if (structObj["range_cos_max_tilt"].IsBool()){
			_params.range_cos_max_tilt = NAN;
		}else{
			_params.range_cos_max_tilt = structObj["range_cos_max_tilt"].GetFloat();
		}
		if (structObj["range_kin_consistency_gate"].IsBool()){
			_params.range_kin_consistency_gate = NAN;
		}else{
			_params.range_kin_consistency_gate = structObj["range_kin_consistency_gate"].GetFloat();
		}
		if (structObj["ev_vel_innov_gate"].IsBool()){
			_params.ev_vel_innov_gate = NAN;
		}else{
			_params.ev_vel_innov_gate = structObj["ev_vel_innov_gate"].GetFloat();
		}
		if (structObj["ev_pos_innov_gate"].IsBool()){
			_params.ev_pos_innov_gate = NAN;
		}else{
			_params.ev_pos_innov_gate = structObj["ev_pos_innov_gate"].GetFloat();
		}
		if (structObj["flow_noise"].IsBool()){
			_params.flow_noise = NAN;
		}else{
			_params.flow_noise = structObj["flow_noise"].GetFloat();
		}
		if (structObj["flow_noise_qual_min"].IsBool()){
			_params.flow_noise_qual_min = NAN;
		}else{
			_params.flow_noise_qual_min = structObj["flow_noise_qual_min"].GetFloat();
		}
			_params.flow_qual_min = structObj["flow_qual_min"].GetInt();
		if (structObj["flow_innov_gate"].IsBool()){
			_params.flow_innov_gate = NAN;
		}else{
			_params.flow_innov_gate = structObj["flow_innov_gate"].GetFloat();
		}
			_params.gps_check_mask = structObj["gps_check_mask"].GetInt();
		if (structObj["req_hacc"].IsBool()){
			_params.req_hacc = NAN;
		}else{
			_params.req_hacc = structObj["req_hacc"].GetFloat();
		}
		if (structObj["req_vacc"].IsBool()){
			_params.req_vacc = NAN;
		}else{
			_params.req_vacc = structObj["req_vacc"].GetFloat();
		}
		if (structObj["req_sacc"].IsBool()){
			_params.req_sacc = NAN;
		}else{
			_params.req_sacc = structObj["req_sacc"].GetFloat();
		}
			_params.req_nsats = structObj["req_nsats"].GetInt();
		if (structObj["req_pdop"].IsBool()){
			_params.req_pdop = NAN;
		}else{
			_params.req_pdop = structObj["req_pdop"].GetFloat();
		}
		if (structObj["req_hdrift"].IsBool()){
			_params.req_hdrift = NAN;
		}else{
			_params.req_hdrift = structObj["req_hdrift"].GetFloat();
		}
		if (structObj["req_vdrift"].IsBool()){
			_params.req_vdrift = NAN;
		}else{
			_params.req_vdrift = structObj["req_vdrift"].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_params.imu_pos_body(i) = structObj["imu_pos_body"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_params.gps_pos_body(i) = structObj["gps_pos_body"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_params.rng_pos_body(i) = structObj["rng_pos_body"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_params.flow_pos_body(i) = structObj["flow_pos_body"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_params.ev_pos_body(i) = structObj["ev_pos_body"][i].GetFloat();
		}
		if (structObj["vel_Tau"].IsBool()){
			_params.vel_Tau = NAN;
		}else{
			_params.vel_Tau = structObj["vel_Tau"].GetFloat();
		}
		if (structObj["pos_Tau"].IsBool()){
			_params.pos_Tau = NAN;
		}else{
			_params.pos_Tau = structObj["pos_Tau"].GetFloat();
		}
		if (structObj["acc_bias_lim"].IsBool()){
			_params.acc_bias_lim = NAN;
		}else{
			_params.acc_bias_lim = structObj["acc_bias_lim"].GetFloat();
		}
		if (structObj["acc_bias_learn_acc_lim"].IsBool()){
			_params.acc_bias_learn_acc_lim = NAN;
		}else{
			_params.acc_bias_learn_acc_lim = structObj["acc_bias_learn_acc_lim"].GetFloat();
		}
		if (structObj["acc_bias_learn_gyr_lim"].IsBool()){
			_params.acc_bias_learn_gyr_lim = NAN;
		}else{
			_params.acc_bias_learn_gyr_lim = structObj["acc_bias_learn_gyr_lim"].GetFloat();
		}
		if (structObj["acc_bias_learn_tc"].IsBool()){
			_params.acc_bias_learn_tc = NAN;
		}else{
			_params.acc_bias_learn_tc = structObj["acc_bias_learn_tc"].GetFloat();
		}
			_params.valid_timeout_max = structObj["valid_timeout_max"].GetInt();
		if (structObj["static_pressure_coef_xp"].IsBool()){
			_params.static_pressure_coef_xp = NAN;
		}else{
			_params.static_pressure_coef_xp = structObj["static_pressure_coef_xp"].GetFloat();
		}
		if (structObj["static_pressure_coef_xn"].IsBool()){
			_params.static_pressure_coef_xn = NAN;
		}else{
			_params.static_pressure_coef_xn = structObj["static_pressure_coef_xn"].GetFloat();
		}
		if (structObj["static_pressure_coef_yp"].IsBool()){
			_params.static_pressure_coef_yp = NAN;
		}else{
			_params.static_pressure_coef_yp = structObj["static_pressure_coef_yp"].GetFloat();
		}
		if (structObj["static_pressure_coef_yn"].IsBool()){
			_params.static_pressure_coef_yn = NAN;
		}else{
			_params.static_pressure_coef_yn = structObj["static_pressure_coef_yn"].GetFloat();
		}
		if (structObj["static_pressure_coef_z"].IsBool()){
			_params.static_pressure_coef_z = NAN;
		}else{
			_params.static_pressure_coef_z = structObj["static_pressure_coef_z"].GetFloat();
		}
		if (structObj["max_correction_airspeed"].IsBool()){
			_params.max_correction_airspeed = NAN;
		}else{
			_params.max_correction_airspeed = structObj["max_correction_airspeed"].GetFloat();
		}
		if (structObj["drag_noise"].IsBool()){
			_params.drag_noise = NAN;
		}else{
			_params.drag_noise = structObj["drag_noise"].GetFloat();
		}
		if (structObj["bcoef_x"].IsBool()){
			_params.bcoef_x = NAN;
		}else{
			_params.bcoef_x = structObj["bcoef_x"].GetFloat();
		}
		if (structObj["bcoef_y"].IsBool()){
			_params.bcoef_y = NAN;
		}else{
			_params.bcoef_y = structObj["bcoef_y"].GetFloat();
		}
		if (structObj["mcoef"].IsBool()){
			_params.mcoef = NAN;
		}else{
			_params.mcoef = structObj["mcoef"].GetFloat();
		}
			_params.synthesize_mag_z = structObj["synthesize_mag_z"].GetInt();
			_params.check_mag_strength = structObj["check_mag_strength"].GetInt();
		if (structObj["EKFGSF_tas_default"].IsBool()){
			_params.EKFGSF_tas_default = NAN;
		}else{
			_params.EKFGSF_tas_default = structObj["EKFGSF_tas_default"].GetFloat();
		}
}
{
		_obs_buffer_length = ekfObj["_obs_buffer_length"].GetUint();
}
{
		_imu_buffer_length = ekfObj["_imu_buffer_length"].GetUint();
}
{
	if (ekfObj["_dt_imu_avg"].IsBool()){
		_dt_imu_avg = NAN;
	}else{
		_dt_imu_avg = ekfObj["_dt_imu_avg"].GetFloat();
	}
}
{
	if (ekfObj["_dt_ekf_avg"].IsBool()){
		_dt_ekf_avg = NAN;
	}else{
		_dt_ekf_avg = ekfObj["_dt_ekf_avg"].GetFloat();
	}
}
{
	rapidjson::Value& structObj = ekfObj["_imu_sample_delayed"];
			_imu_sample_delayed.time_us = structObj["time_us"].GetUint64();
		for(int i = 0; i < 3; i++){
			_imu_sample_delayed.delta_ang(i) = structObj["delta_ang"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_imu_sample_delayed.delta_vel(i) = structObj["delta_vel"][i].GetFloat();
		}
		if (structObj["delta_ang_dt"].IsBool()){
			_imu_sample_delayed.delta_ang_dt = NAN;
		}else{
			_imu_sample_delayed.delta_ang_dt = structObj["delta_ang_dt"].GetFloat();
		}
		if (structObj["delta_vel_dt"].IsBool()){
			_imu_sample_delayed.delta_vel_dt = NAN;
		}else{
			_imu_sample_delayed.delta_vel_dt = structObj["delta_vel_dt"].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_imu_sample_delayed.delta_vel_clipping[i] = structObj["delta_vel_clipping"][i].GetBool();
		}
}
{
	rapidjson::Value& structObj = ekfObj["_baro_sample_delayed"];
			_baro_sample_delayed.time_us = structObj["time_us"].GetUint64();
		if (structObj["hgt"].IsBool()){
			_baro_sample_delayed.hgt = NAN;
		}else{
			_baro_sample_delayed.hgt = structObj["hgt"].GetFloat();
		}
}
{
	rapidjson::Value& structObj = ekfObj["_gps_sample_delayed"];
			_gps_sample_delayed.time_us = structObj["time_us"].GetUint64();
		for(int i = 0; i < 2; i++){
			_gps_sample_delayed.pos(i) = structObj["pos"][i].GetFloat();
		}
		if (structObj["hgt"].IsBool()){
			_gps_sample_delayed.hgt = NAN;
		}else{
			_gps_sample_delayed.hgt = structObj["hgt"].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_gps_sample_delayed.vel(i) = structObj["vel"][i].GetFloat();
		}
		if (structObj["yaw"].IsBool()){
			_gps_sample_delayed.yaw = NAN;
		}else{
			_gps_sample_delayed.yaw = structObj["yaw"].GetFloat();
		}
		if (structObj["hacc"].IsBool()){
			_gps_sample_delayed.hacc = NAN;
		}else{
			_gps_sample_delayed.hacc = structObj["hacc"].GetFloat();
		}
		if (structObj["vacc"].IsBool()){
			_gps_sample_delayed.vacc = NAN;
		}else{
			_gps_sample_delayed.vacc = structObj["vacc"].GetFloat();
		}
		if (structObj["sacc"].IsBool()){
			_gps_sample_delayed.sacc = NAN;
		}else{
			_gps_sample_delayed.sacc = structObj["sacc"].GetFloat();
		}
}
{
}
{
	rapidjson::Value& structObj = ekfObj["_airspeed_sample_delayed"];
			_airspeed_sample_delayed.time_us = structObj["time_us"].GetUint64();
		if (structObj["true_airspeed"].IsBool()){
			_airspeed_sample_delayed.true_airspeed = NAN;
		}else{
			_airspeed_sample_delayed.true_airspeed = structObj["true_airspeed"].GetFloat();
		}
		if (structObj["eas2tas"].IsBool()){
			_airspeed_sample_delayed.eas2tas = NAN;
		}else{
			_airspeed_sample_delayed.eas2tas = structObj["eas2tas"].GetFloat();
		}
}
{
	rapidjson::Value& structObj = ekfObj["_flow_sample_delayed"];
			_flow_sample_delayed.time_us = structObj["time_us"].GetUint64();
		for(int i = 0; i < 2; i++){
			_flow_sample_delayed.flow_xy_rad(i) = structObj["flow_xy_rad"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_flow_sample_delayed.gyro_xyz(i) = structObj["gyro_xyz"][i].GetFloat();
		}
		if (structObj["dt"].IsBool()){
			_flow_sample_delayed.dt = NAN;
		}else{
			_flow_sample_delayed.dt = structObj["dt"].GetFloat();
		}
			_flow_sample_delayed.quality = structObj["quality"].GetUint();
}
{
	rapidjson::Value& structObj = ekfObj["_ev_sample_delayed"];
			_ev_sample_delayed.time_us = structObj["time_us"].GetUint64();
		for(int i = 0; i < 3; i++){
			_ev_sample_delayed.pos(i) = structObj["pos"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_ev_sample_delayed.vel(i) = structObj["vel"][i].GetFloat();
		}
		for(int i = 0; i < 4; i++){
			_ev_sample_delayed.quat(i) = structObj["quat"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_ev_sample_delayed.posVar(i) = structObj["posVar"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				_ev_sample_delayed.velCov(i, j) = structObj["velCov"][i*3 + j].GetFloat();
			}
		}
		if (structObj["angVar"].IsBool()){
			_ev_sample_delayed.angVar = NAN;
		}else{
			_ev_sample_delayed.angVar = structObj["angVar"].GetFloat();
		}
			_ev_sample_delayed.reset_counter = structObj["reset_counter"].GetUint();
}
{
	rapidjson::Value& structObj = ekfObj["_ev_sample_delayed_prev"];
			_ev_sample_delayed_prev.time_us = structObj["time_us"].GetUint64();
		for(int i = 0; i < 3; i++){
			_ev_sample_delayed_prev.pos(i) = structObj["pos"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_ev_sample_delayed_prev.vel(i) = structObj["vel"][i].GetFloat();
		}
		for(int i = 0; i < 4; i++){
			_ev_sample_delayed_prev.quat(i) = structObj["quat"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_ev_sample_delayed_prev.posVar(i) = structObj["posVar"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				_ev_sample_delayed_prev.velCov(i, j) = structObj["velCov"][i*3 + j].GetFloat();
			}
		}
		if (structObj["angVar"].IsBool()){
			_ev_sample_delayed_prev.angVar = NAN;
		}else{
			_ev_sample_delayed_prev.angVar = structObj["angVar"].GetFloat();
		}
			_ev_sample_delayed_prev.reset_counter = structObj["reset_counter"].GetUint();
}
{
	rapidjson::Value& structObj = ekfObj["_drag_down_sampled"];
			_drag_down_sampled.time_us = structObj["time_us"].GetUint64();
		for(int i = 0; i < 2; i++){
			_drag_down_sampled.accelXY(i) = structObj["accelXY"][i].GetFloat();
		}
}
{
}
{
	if (ekfObj["_air_density"].IsBool()){
		_air_density = NAN;
	}else{
		_air_density = ekfObj["_air_density"].GetFloat();
	}
}
{
	if (ekfObj["_flow_max_rate"].IsBool()){
		_flow_max_rate = NAN;
	}else{
		_flow_max_rate = ekfObj["_flow_max_rate"].GetFloat();
	}
}
{
	if (ekfObj["_flow_min_distance"].IsBool()){
		_flow_min_distance = NAN;
	}else{
		_flow_min_distance = ekfObj["_flow_min_distance"].GetFloat();
	}
}
{
	if (ekfObj["_flow_max_distance"].IsBool()){
		_flow_max_distance = NAN;
	}else{
		_flow_max_distance = ekfObj["_flow_max_distance"].GetFloat();
	}
}
{
	rapidjson::Value& structObj = ekfObj["_output_new"];
			_output_new.time_us = structObj["time_us"].GetUint64();
		for(int i = 0; i < 4; i++){
			_output_new.quat_nominal(i) = structObj["quat_nominal"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_output_new.vel(i) = structObj["vel"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_output_new.pos(i) = structObj["pos"][i].GetFloat();
		}
}
{
	rapidjson::Value& structObj = ekfObj["_output_vert_new"];
			_output_vert_new.time_us = structObj["time_us"].GetUint64();
		if (structObj["vert_vel"].IsBool()){
			_output_vert_new.vert_vel = NAN;
		}else{
			_output_vert_new.vert_vel = structObj["vert_vel"].GetFloat();
		}
		if (structObj["vert_vel_integ"].IsBool()){
			_output_vert_new.vert_vel_integ = NAN;
		}else{
			_output_vert_new.vert_vel_integ = structObj["vert_vel_integ"].GetFloat();
		}
		if (structObj["dt"].IsBool()){
			_output_vert_new.dt = NAN;
		}else{
			_output_vert_new.dt = structObj["dt"].GetFloat();
		}
}
{
	rapidjson::Value& structObj = ekfObj["_newest_high_rate_imu_sample"];
			_newest_high_rate_imu_sample.time_us = structObj["time_us"].GetUint64();
		for(int i = 0; i < 3; i++){
			_newest_high_rate_imu_sample.delta_ang(i) = structObj["delta_ang"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_newest_high_rate_imu_sample.delta_vel(i) = structObj["delta_vel"][i].GetFloat();
		}
		if (structObj["delta_ang_dt"].IsBool()){
			_newest_high_rate_imu_sample.delta_ang_dt = NAN;
		}else{
			_newest_high_rate_imu_sample.delta_ang_dt = structObj["delta_ang_dt"].GetFloat();
		}
		if (structObj["delta_vel_dt"].IsBool()){
			_newest_high_rate_imu_sample.delta_vel_dt = NAN;
		}else{
			_newest_high_rate_imu_sample.delta_vel_dt = structObj["delta_vel_dt"].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_newest_high_rate_imu_sample.delta_vel_clipping[i] = structObj["delta_vel_clipping"][i].GetBool();
		}
}
{
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			_R_to_earth_now(i, j) = ekfObj["_R_to_earth_now"][i*3 + j].GetFloat();
		}
	}
}
{
	for(int i = 0; i < 3; i++){
		_vel_imu_rel_body_ned(i) = ekfObj["_vel_imu_rel_body_ned"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_vel_deriv(i) = ekfObj["_vel_deriv"][i].GetFloat();
	}
}
{
		_imu_updated = ekfObj["_imu_updated"].GetBool();
}
{
		_initialised = ekfObj["_initialised"].GetBool();
}
{
		_NED_origin_initialised = ekfObj["_NED_origin_initialised"].GetBool();
}
{
		_gps_speed_valid = ekfObj["_gps_speed_valid"].GetBool();
}
{
	if (ekfObj["_gps_origin_eph"].IsBool()){
		_gps_origin_eph = NAN;
	}else{
		_gps_origin_eph = ekfObj["_gps_origin_eph"].GetFloat();
	}
}
{
	if (ekfObj["_gps_origin_epv"].IsBool()){
		_gps_origin_epv = NAN;
	}else{
		_gps_origin_epv = ekfObj["_gps_origin_epv"].GetFloat();
	}
}
{
	rapidjson::Value& structObj = ekfObj["_pos_ref"];
		_pos_ref.set(structObj["_ref_timestamp"].GetUint64(), structObj["_ref_lat"].GetDouble(), structObj["_ref_lon"].GetDouble(), structObj["_ref_sin_lat"].GetDouble(), structObj["_ref_cos_lat"].GetDouble(), structObj["_ref_init_done"].GetBool());}
{
	rapidjson::Value& structObj = ekfObj["_gps_pos_prev"];
		_gps_pos_prev.set(structObj["_ref_timestamp"].GetUint64(), structObj["_ref_lat"].GetDouble(), structObj["_ref_lon"].GetDouble(), structObj["_ref_sin_lat"].GetDouble(), structObj["_ref_cos_lat"].GetDouble(), structObj["_ref_init_done"].GetBool());}
{
	if (ekfObj["_gps_alt_prev"].IsBool()){
		_gps_alt_prev = NAN;
	}else{
		_gps_alt_prev = ekfObj["_gps_alt_prev"].GetFloat();
	}
}
{
	if (ekfObj["_gps_yaw_offset"].IsBool()){
		_gps_yaw_offset = NAN;
	}else{
		_gps_yaw_offset = ekfObj["_gps_yaw_offset"].GetFloat();
	}
}
{
	if (ekfObj["_yaw_test_ratio"].IsBool()){
		_yaw_test_ratio = NAN;
	}else{
		_yaw_test_ratio = ekfObj["_yaw_test_ratio"].GetFloat();
	}
}
	{
		auto & afJson = ekfObj["_yaw_signed_test_ratio_lpf"];
		_yaw_signed_test_ratio_lpf.setCutoff(afJson["_cutoff_freq"].GetFloat());
		_yaw_signed_test_ratio_lpf.setAlpha(afJson["_alpha"].GetFloat());
		_yaw_signed_test_ratio_lpf.setState(afJson["_filter_state"].GetFloat());
	}
{
	for(int i = 0; i < 3; i++){
		_mag_test_ratio(i) = ekfObj["_mag_test_ratio"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 2; i++){
		_gps_vel_test_ratio(i) = ekfObj["_gps_vel_test_ratio"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 2; i++){
		_gps_pos_test_ratio(i) = ekfObj["_gps_pos_test_ratio"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 2; i++){
		_ev_vel_test_ratio(i) = ekfObj["_ev_vel_test_ratio"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 2; i++){
		_ev_pos_test_ratio(i) = ekfObj["_ev_pos_test_ratio"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 2; i++){
		_aux_vel_test_ratio(i) = ekfObj["_aux_vel_test_ratio"][i].GetFloat();
	}
}
{
	if (ekfObj["_baro_hgt_test_ratio"].IsBool()){
		_baro_hgt_test_ratio = NAN;
	}else{
		_baro_hgt_test_ratio = ekfObj["_baro_hgt_test_ratio"].GetFloat();
	}
}
{
	if (ekfObj["_rng_hgt_test_ratio"].IsBool()){
		_rng_hgt_test_ratio = NAN;
	}else{
		_rng_hgt_test_ratio = ekfObj["_rng_hgt_test_ratio"].GetFloat();
	}
}
{
	if (ekfObj["_optflow_test_ratio"].IsBool()){
		_optflow_test_ratio = NAN;
	}else{
		_optflow_test_ratio = ekfObj["_optflow_test_ratio"].GetFloat();
	}
}
{
	if (ekfObj["_tas_test_ratio"].IsBool()){
		_tas_test_ratio = NAN;
	}else{
		_tas_test_ratio = ekfObj["_tas_test_ratio"].GetFloat();
	}
}
{
	if (ekfObj["_hagl_test_ratio"].IsBool()){
		_hagl_test_ratio = NAN;
	}else{
		_hagl_test_ratio = ekfObj["_hagl_test_ratio"].GetFloat();
	}
}
{
	if (ekfObj["_beta_test_ratio"].IsBool()){
		_beta_test_ratio = NAN;
	}else{
		_beta_test_ratio = ekfObj["_beta_test_ratio"].GetFloat();
	}
}
{
	for(int i = 0; i < 2; i++){
		_drag_test_ratio(i) = ekfObj["_drag_test_ratio"][i].GetFloat();
	}
}
	{
		rapidjson::Value& innerJson = ekfObj["_innov_check_fail_status"]["flags"];
		_innov_check_fail_status.flags.reject_airspeed = innerJson["reject_airspeed"].GetBool();
		_innov_check_fail_status.flags.reject_hagl = innerJson["reject_hagl"].GetBool();
		_innov_check_fail_status.flags.reject_hor_pos = innerJson["reject_hor_pos"].GetBool();
		_innov_check_fail_status.flags.reject_hor_vel = innerJson["reject_hor_vel"].GetBool();
		_innov_check_fail_status.flags.reject_mag_x = innerJson["reject_mag_x"].GetBool();
		_innov_check_fail_status.flags.reject_mag_y = innerJson["reject_mag_y"].GetBool();
		_innov_check_fail_status.flags.reject_mag_z = innerJson["reject_mag_z"].GetBool();
		_innov_check_fail_status.flags.reject_optflow_X = innerJson["reject_optflow_X"].GetBool();
		_innov_check_fail_status.flags.reject_optflow_Y = innerJson["reject_optflow_Y"].GetBool();
		_innov_check_fail_status.flags.reject_sideslip = innerJson["reject_sideslip"].GetBool();
		_innov_check_fail_status.flags.reject_ver_pos = innerJson["reject_ver_pos"].GetBool();
		_innov_check_fail_status.flags.reject_ver_vel = innerJson["reject_ver_vel"].GetBool();
		_innov_check_fail_status.flags.reject_yaw = innerJson["reject_yaw"].GetBool();
}{
		_deadreckon_time_exceeded = ekfObj["_deadreckon_time_exceeded"].GetBool();
}
{
	if (ekfObj["_gps_horizontal_position_drift_rate_m_s"].IsBool()){
		_gps_horizontal_position_drift_rate_m_s = NAN;
	}else{
		_gps_horizontal_position_drift_rate_m_s = ekfObj["_gps_horizontal_position_drift_rate_m_s"].GetFloat();
	}
}
{
	if (ekfObj["_gps_vertical_position_drift_rate_m_s"].IsBool()){
		_gps_vertical_position_drift_rate_m_s = NAN;
	}else{
		_gps_vertical_position_drift_rate_m_s = ekfObj["_gps_vertical_position_drift_rate_m_s"].GetFloat();
	}
}
{
	if (ekfObj["_gps_filtered_horizontal_velocity_m_s"].IsBool()){
		_gps_filtered_horizontal_velocity_m_s = NAN;
	}else{
		_gps_filtered_horizontal_velocity_m_s = ekfObj["_gps_filtered_horizontal_velocity_m_s"].GetFloat();
	}
}
{
		_time_last_on_ground_us = ekfObj["_time_last_on_ground_us"].GetUint64();
}
{
		_time_last_in_air = ekfObj["_time_last_in_air"].GetUint64();
}
	if(ekfObj.HasMember("_imu_buffer")){
		rapidjson::Value & imuSample_buffer = ekfObj["_imu_buffer"];
		_imu_buffer.allocate(imuSample_buffer["_size"].GetUint());
		_imu_buffer.set_head(imuSample_buffer["_head"].GetUint());
		_imu_buffer.set_tail(imuSample_buffer["_tail"].GetUint());
		_imu_buffer.set_first_write(imuSample_buffer["_first_write"].GetBool());
		auto & array = imuSample_buffer["_buffer"];
		for(unsigned int index = 0; index < std::min(array.Size(),imuSample_buffer["_size"].GetUint()) ; index++){
			imuSample elem;
					elem.time_us = array[index]["time_us"].GetUint64();
				for(int i = 0; i < 3; i++){
					elem.delta_ang(i) = array[index]["delta_ang"][i].GetFloat();
				}
				for(int i = 0; i < 3; i++){
					elem.delta_vel(i) = array[index]["delta_vel"][i].GetFloat();
				}
				if (array[index]["delta_ang_dt"].IsBool()){
					elem.delta_ang_dt = NAN;
				}else{
					elem.delta_ang_dt = array[index]["delta_ang_dt"].GetFloat();
				}
				if (array[index]["delta_vel_dt"].IsBool()){
					elem.delta_vel_dt = NAN;
				}else{
					elem.delta_vel_dt = array[index]["delta_vel_dt"].GetFloat();
				}
				for(int i = 0; i < 3; i++){
					elem.delta_vel_clipping[i] = array[index]["delta_vel_clipping"][i].GetBool();
				}
			_imu_buffer.set_data(elem, index);
		}	}	if(ekfObj.HasMember("_output_buffer")){
		rapidjson::Value & outputSample_buffer = ekfObj["_output_buffer"];
		_output_buffer.allocate(outputSample_buffer["_size"].GetUint());
		_output_buffer.set_head(outputSample_buffer["_head"].GetUint());
		_output_buffer.set_tail(outputSample_buffer["_tail"].GetUint());
		_output_buffer.set_first_write(outputSample_buffer["_first_write"].GetBool());
		auto & array = outputSample_buffer["_buffer"];
		for(unsigned int index = 0; index < std::min(array.Size(),outputSample_buffer["_size"].GetUint()) ; index++){
			outputSample elem;
					elem.time_us = array[index]["time_us"].GetUint64();
				for(int i = 0; i < 4; i++){
					elem.quat_nominal(i) = array[index]["quat_nominal"][i].GetFloat();
				}
				for(int i = 0; i < 3; i++){
					elem.vel(i) = array[index]["vel"][i].GetFloat();
				}
				for(int i = 0; i < 3; i++){
					elem.pos(i) = array[index]["pos"][i].GetFloat();
				}
			_output_buffer.set_data(elem, index);
		}	}	if(ekfObj.HasMember("_output_vert_buffer")){
		rapidjson::Value & outputVert_buffer = ekfObj["_output_vert_buffer"];
		_output_vert_buffer.allocate(outputVert_buffer["_size"].GetUint());
		_output_vert_buffer.set_head(outputVert_buffer["_head"].GetUint());
		_output_vert_buffer.set_tail(outputVert_buffer["_tail"].GetUint());
		_output_vert_buffer.set_first_write(outputVert_buffer["_first_write"].GetBool());
		auto & array = outputVert_buffer["_buffer"];
		for(unsigned int index = 0; index < std::min(array.Size(),outputVert_buffer["_size"].GetUint()) ; index++){
			outputVert elem;
					elem.time_us = array[index]["time_us"].GetUint64();
				if (array[index]["vert_vel"].IsBool()){
					elem.vert_vel = NAN;
				}else{
					elem.vert_vel = array[index]["vert_vel"].GetFloat();
				}
				if (array[index]["vert_vel_integ"].IsBool()){
					elem.vert_vel_integ = NAN;
				}else{
					elem.vert_vel_integ = array[index]["vert_vel_integ"].GetFloat();
				}
				if (array[index]["dt"].IsBool()){
					elem.dt = NAN;
				}else{
					elem.dt = array[index]["dt"].GetFloat();
				}
			_output_vert_buffer.set_data(elem, index);
		}	}	if(ekfObj.HasMember("_gps_buffer")){
		rapidjson::Value & gpsSample_buffer = ekfObj["_gps_buffer"];
		if(_gps_buffer==nullptr){
			_gps_buffer = new RingBuffer<gpsSample>(gpsSample_buffer["_size"].GetUint());
		}
		_gps_buffer->allocate(gpsSample_buffer["_size"].GetUint());
		_gps_buffer->set_head(gpsSample_buffer["_head"].GetUint());
		_gps_buffer->set_tail(gpsSample_buffer["_tail"].GetUint());
		_gps_buffer->set_first_write(gpsSample_buffer["_first_write"].GetBool());
		auto & array = gpsSample_buffer["_buffer"];
		for(unsigned int index = 0; index < std::min(array.Size(),gpsSample_buffer["_size"].GetUint()) ; index++){
			gpsSample elem;
					elem.time_us = array[index]["time_us"].GetUint64();
				for(int i = 0; i < 2; i++){
					elem.pos(i) = array[index]["pos"][i].GetFloat();
				}
				if (array[index]["hgt"].IsBool()){
					elem.hgt = NAN;
				}else{
					elem.hgt = array[index]["hgt"].GetFloat();
				}
				for(int i = 0; i < 3; i++){
					elem.vel(i) = array[index]["vel"][i].GetFloat();
				}
				if (array[index]["yaw"].IsBool()){
					elem.yaw = NAN;
				}else{
					elem.yaw = array[index]["yaw"].GetFloat();
				}
				if (array[index]["hacc"].IsBool()){
					elem.hacc = NAN;
				}else{
					elem.hacc = array[index]["hacc"].GetFloat();
				}
				if (array[index]["vacc"].IsBool()){
					elem.vacc = NAN;
				}else{
					elem.vacc = array[index]["vacc"].GetFloat();
				}
				if (array[index]["sacc"].IsBool()){
					elem.sacc = NAN;
				}else{
					elem.sacc = array[index]["sacc"].GetFloat();
				}
			_gps_buffer->set_data(elem, index);
		}	}	if(ekfObj.HasMember("_mag_buffer")){
		rapidjson::Value & magSample_buffer = ekfObj["_mag_buffer"];
		if(_mag_buffer==nullptr){
			_mag_buffer = new RingBuffer<magSample>(magSample_buffer["_size"].GetUint());
		}
		_mag_buffer->allocate(magSample_buffer["_size"].GetUint());
		_mag_buffer->set_head(magSample_buffer["_head"].GetUint());
		_mag_buffer->set_tail(magSample_buffer["_tail"].GetUint());
		_mag_buffer->set_first_write(magSample_buffer["_first_write"].GetBool());
		auto & array = magSample_buffer["_buffer"];
		for(unsigned int index = 0; index < std::min(array.Size(),magSample_buffer["_size"].GetUint()) ; index++){
			magSample elem;
					elem.time_us = array[index]["time_us"].GetUint64();
				for(int i = 0; i < 3; i++){
					elem.mag(i) = array[index]["mag"][i].GetFloat();
				}
			_mag_buffer->set_data(elem, index);
		}	}	if(ekfObj.HasMember("_baro_buffer")){
		rapidjson::Value & baroSample_buffer = ekfObj["_baro_buffer"];
		if(_baro_buffer==nullptr){
			_baro_buffer = new RingBuffer<baroSample>(baroSample_buffer["_size"].GetUint());
		}
		_baro_buffer->allocate(baroSample_buffer["_size"].GetUint());
		_baro_buffer->set_head(baroSample_buffer["_head"].GetUint());
		_baro_buffer->set_tail(baroSample_buffer["_tail"].GetUint());
		_baro_buffer->set_first_write(baroSample_buffer["_first_write"].GetBool());
		auto & array = baroSample_buffer["_buffer"];
		for(unsigned int index = 0; index < std::min(array.Size(),baroSample_buffer["_size"].GetUint()) ; index++){
			baroSample elem;
					elem.time_us = array[index]["time_us"].GetUint64();
				if (array[index]["hgt"].IsBool()){
					elem.hgt = NAN;
				}else{
					elem.hgt = array[index]["hgt"].GetFloat();
				}
			_baro_buffer->set_data(elem, index);
		}	}	if(ekfObj.HasMember("_range_buffer")){
		rapidjson::Value & rangeSample_buffer = ekfObj["_range_buffer"];
		if(_range_buffer==nullptr){
			_range_buffer = new RingBuffer<rangeSample>(rangeSample_buffer["_size"].GetUint());
		}
		_range_buffer->allocate(rangeSample_buffer["_size"].GetUint());
		_range_buffer->set_head(rangeSample_buffer["_head"].GetUint());
		_range_buffer->set_tail(rangeSample_buffer["_tail"].GetUint());
		_range_buffer->set_first_write(rangeSample_buffer["_first_write"].GetBool());
		auto & array = rangeSample_buffer["_buffer"];
		for(unsigned int index = 0; index < std::min(array.Size(),rangeSample_buffer["_size"].GetUint()) ; index++){
			rangeSample elem;
					elem.time_us = array[index]["time_us"].GetUint64();
				if (array[index]["rng"].IsBool()){
					elem.rng = NAN;
				}else{
					elem.rng = array[index]["rng"].GetFloat();
				}
			_range_buffer->set_data(elem, index);
		}	}	if(ekfObj.HasMember("_airspeed_buffer")){
		rapidjson::Value & airspeedSample_buffer = ekfObj["_airspeed_buffer"];
		if(_airspeed_buffer==nullptr){
			_airspeed_buffer = new RingBuffer<airspeedSample>(airspeedSample_buffer["_size"].GetUint());
		}
		_airspeed_buffer->allocate(airspeedSample_buffer["_size"].GetUint());
		_airspeed_buffer->set_head(airspeedSample_buffer["_head"].GetUint());
		_airspeed_buffer->set_tail(airspeedSample_buffer["_tail"].GetUint());
		_airspeed_buffer->set_first_write(airspeedSample_buffer["_first_write"].GetBool());
		auto & array = airspeedSample_buffer["_buffer"];
		for(unsigned int index = 0; index < std::min(array.Size(),airspeedSample_buffer["_size"].GetUint()) ; index++){
			airspeedSample elem;
					elem.time_us = array[index]["time_us"].GetUint64();
				if (array[index]["true_airspeed"].IsBool()){
					elem.true_airspeed = NAN;
				}else{
					elem.true_airspeed = array[index]["true_airspeed"].GetFloat();
				}
				if (array[index]["eas2tas"].IsBool()){
					elem.eas2tas = NAN;
				}else{
					elem.eas2tas = array[index]["eas2tas"].GetFloat();
				}
			_airspeed_buffer->set_data(elem, index);
		}	}	if(ekfObj.HasMember("_flow_buffer")){
		rapidjson::Value & flowSample_buffer = ekfObj["_flow_buffer"];
		if(_flow_buffer==nullptr){
			_flow_buffer = new RingBuffer<flowSample>(flowSample_buffer["_size"].GetUint());
		}
		_flow_buffer->allocate(flowSample_buffer["_size"].GetUint());
		_flow_buffer->set_head(flowSample_buffer["_head"].GetUint());
		_flow_buffer->set_tail(flowSample_buffer["_tail"].GetUint());
		_flow_buffer->set_first_write(flowSample_buffer["_first_write"].GetBool());
		auto & array = flowSample_buffer["_buffer"];
		for(unsigned int index = 0; index < std::min(array.Size(),flowSample_buffer["_size"].GetUint()) ; index++){
			flowSample elem;
					elem.time_us = array[index]["time_us"].GetUint64();
				for(int i = 0; i < 2; i++){
					elem.flow_xy_rad(i) = array[index]["flow_xy_rad"][i].GetFloat();
				}
				for(int i = 0; i < 3; i++){
					elem.gyro_xyz(i) = array[index]["gyro_xyz"][i].GetFloat();
				}
				if (array[index]["dt"].IsBool()){
					elem.dt = NAN;
				}else{
					elem.dt = array[index]["dt"].GetFloat();
				}
					elem.quality = array[index]["quality"].GetUint();
			_flow_buffer->set_data(elem, index);
		}	}	if(ekfObj.HasMember("_ext_vision_buffer")){
		rapidjson::Value & extVisionSample_buffer = ekfObj["_ext_vision_buffer"];
		if(_ext_vision_buffer==nullptr){
			_ext_vision_buffer = new RingBuffer<extVisionSample>(extVisionSample_buffer["_size"].GetUint());
		}
		_ext_vision_buffer->allocate(extVisionSample_buffer["_size"].GetUint());
		_ext_vision_buffer->set_head(extVisionSample_buffer["_head"].GetUint());
		_ext_vision_buffer->set_tail(extVisionSample_buffer["_tail"].GetUint());
		_ext_vision_buffer->set_first_write(extVisionSample_buffer["_first_write"].GetBool());
		auto & array = extVisionSample_buffer["_buffer"];
		for(unsigned int index = 0; index < std::min(array.Size(),extVisionSample_buffer["_size"].GetUint()) ; index++){
			extVisionSample elem;
					elem.time_us = array[index]["time_us"].GetUint64();
				for(int i = 0; i < 3; i++){
					elem.pos(i) = array[index]["pos"][i].GetFloat();
				}
				for(int i = 0; i < 3; i++){
					elem.vel(i) = array[index]["vel"][i].GetFloat();
				}
				for(int i = 0; i < 4; i++){
					elem.quat(i) = array[index]["quat"][i].GetFloat();
				}
				for(int i = 0; i < 3; i++){
					elem.posVar(i) = array[index]["posVar"][i].GetFloat();
				}
				for(int i = 0; i < 3; i++){
					for(int j = 0; j < 3; j++){
						elem.velCov(i, j) = array[index]["velCov"][i*3 + j].GetFloat();
					}
				}
				if (array[index]["angVar"].IsBool()){
					elem.angVar = NAN;
				}else{
					elem.angVar = array[index]["angVar"].GetFloat();
				}
					elem.reset_counter = array[index]["reset_counter"].GetUint();
			_ext_vision_buffer->set_data(elem, index);
		}	}	if(ekfObj.HasMember("_drag_buffer")){
		rapidjson::Value & dragSample_buffer = ekfObj["_drag_buffer"];
		if(_drag_buffer==nullptr){
			_drag_buffer = new RingBuffer<dragSample>(dragSample_buffer["_size"].GetUint());
		}
		_drag_buffer->allocate(dragSample_buffer["_size"].GetUint());
		_drag_buffer->set_head(dragSample_buffer["_head"].GetUint());
		_drag_buffer->set_tail(dragSample_buffer["_tail"].GetUint());
		_drag_buffer->set_first_write(dragSample_buffer["_first_write"].GetBool());
		auto & array = dragSample_buffer["_buffer"];
		for(unsigned int index = 0; index < std::min(array.Size(),dragSample_buffer["_size"].GetUint()) ; index++){
			dragSample elem;
					elem.time_us = array[index]["time_us"].GetUint64();
				for(int i = 0; i < 2; i++){
					elem.accelXY(i) = array[index]["accelXY"][i].GetFloat();
				}
			_drag_buffer->set_data(elem, index);
		}	}	if(ekfObj.HasMember("_auxvel_buffer")){
		rapidjson::Value & auxVelSample_buffer = ekfObj["_auxvel_buffer"];
		if(_auxvel_buffer==nullptr){
			_auxvel_buffer = new RingBuffer<auxVelSample>(auxVelSample_buffer["_size"].GetUint());
		}
		_auxvel_buffer->allocate(auxVelSample_buffer["_size"].GetUint());
		_auxvel_buffer->set_head(auxVelSample_buffer["_head"].GetUint());
		_auxvel_buffer->set_tail(auxVelSample_buffer["_tail"].GetUint());
		_auxvel_buffer->set_first_write(auxVelSample_buffer["_first_write"].GetBool());
		auto & array = auxVelSample_buffer["_buffer"];
		for(unsigned int index = 0; index < std::min(array.Size(),auxVelSample_buffer["_size"].GetUint()) ; index++){
			auxVelSample elem;
					elem.time_us = array[index]["time_us"].GetUint64();
				for(int i = 0; i < 3; i++){
					elem.vel(i) = array[index]["vel"][i].GetFloat();
				}
				for(int i = 0; i < 3; i++){
					elem.velVar(i) = array[index]["velVar"][i].GetFloat();
				}
			_auxvel_buffer->set_data(elem, index);
		}	}{
		_time_last_imu = ekfObj["_time_last_imu"].GetUint64();
}
{
		_time_last_gps = ekfObj["_time_last_gps"].GetUint64();
}
{
		_time_last_mag = ekfObj["_time_last_mag"].GetUint64();
}
{
		_time_last_baro = ekfObj["_time_last_baro"].GetUint64();
}
{
		_time_last_range = ekfObj["_time_last_range"].GetUint64();
}
{
		_time_last_airspeed = ekfObj["_time_last_airspeed"].GetUint64();
}
{
		_time_last_ext_vision = ekfObj["_time_last_ext_vision"].GetUint64();
}
{
		_time_last_optflow = ekfObj["_time_last_optflow"].GetUint64();
}
{
		_time_last_auxvel = ekfObj["_time_last_auxvel"].GetUint64();
}
{
		_time_last_gnd_effect_on = ekfObj["_time_last_gnd_effect_on"].GetUint64();
}
	{
		rapidjson::Value& innerJson = ekfObj["_fault_status"]["flags"];
		_fault_status.flags.bad_acc_bias = innerJson["bad_acc_bias"].GetBool();
		_fault_status.flags.bad_acc_clipping = innerJson["bad_acc_clipping"].GetBool();
		_fault_status.flags.bad_acc_vertical = innerJson["bad_acc_vertical"].GetBool();
		_fault_status.flags.bad_airspeed = innerJson["bad_airspeed"].GetBool();
		_fault_status.flags.bad_hdg = innerJson["bad_hdg"].GetBool();
		_fault_status.flags.bad_mag_decl = innerJson["bad_mag_decl"].GetBool();
		_fault_status.flags.bad_mag_x = innerJson["bad_mag_x"].GetBool();
		_fault_status.flags.bad_mag_y = innerJson["bad_mag_y"].GetBool();
		_fault_status.flags.bad_mag_z = innerJson["bad_mag_z"].GetBool();
		_fault_status.flags.bad_optflow_X = innerJson["bad_optflow_X"].GetBool();
		_fault_status.flags.bad_optflow_Y = innerJson["bad_optflow_Y"].GetBool();
		_fault_status.flags.bad_pos_D = innerJson["bad_pos_D"].GetBool();
		_fault_status.flags.bad_pos_E = innerJson["bad_pos_E"].GetBool();
		_fault_status.flags.bad_pos_N = innerJson["bad_pos_N"].GetBool();
		_fault_status.flags.bad_sideslip = innerJson["bad_sideslip"].GetBool();
		_fault_status.flags.bad_vel_D = innerJson["bad_vel_D"].GetBool();
		_fault_status.flags.bad_vel_E = innerJson["bad_vel_E"].GetBool();
		_fault_status.flags.bad_vel_N = innerJson["bad_vel_N"].GetBool();
}{
	if (ekfObj["_mag_declination_gps"].IsBool()){
		_mag_declination_gps = NAN;
	}else{
		_mag_declination_gps = ekfObj["_mag_declination_gps"].GetFloat();
	}
}
{
	if (ekfObj["_mag_inclination_gps"].IsBool()){
		_mag_inclination_gps = NAN;
	}else{
		_mag_inclination_gps = ekfObj["_mag_inclination_gps"].GetFloat();
	}
}
{
	if (ekfObj["_mag_strength_gps"].IsBool()){
		_mag_strength_gps = NAN;
	}else{
		_mag_strength_gps = ekfObj["_mag_strength_gps"].GetFloat();
	}
}
	{
		rapidjson::Value& innerJson = ekfObj["_control_status"]["flags"];
		_control_status.flags.baro_hgt = innerJson["baro_hgt"].GetBool();
		_control_status.flags.ev_hgt = innerJson["ev_hgt"].GetBool();
		_control_status.flags.ev_pos = innerJson["ev_pos"].GetBool();
		_control_status.flags.ev_vel = innerJson["ev_vel"].GetBool();
		_control_status.flags.ev_yaw = innerJson["ev_yaw"].GetBool();
		_control_status.flags.fixed_wing = innerJson["fixed_wing"].GetBool();
		_control_status.flags.fuse_aspd = innerJson["fuse_aspd"].GetBool();
		_control_status.flags.fuse_beta = innerJson["fuse_beta"].GetBool();
		_control_status.flags.gnd_effect = innerJson["gnd_effect"].GetBool();
		_control_status.flags.gps = innerJson["gps"].GetBool();
		_control_status.flags.gps_hgt = innerJson["gps_hgt"].GetBool();
		_control_status.flags.gps_yaw = innerJson["gps_yaw"].GetBool();
		_control_status.flags.gps_yaw_fault = innerJson["gps_yaw_fault"].GetBool();
		_control_status.flags.in_air = innerJson["in_air"].GetBool();
		_control_status.flags.inertial_dead_reckoning = innerJson["inertial_dead_reckoning"].GetBool();
		_control_status.flags.mag_3D = innerJson["mag_3D"].GetBool();
		_control_status.flags.mag_aligned_in_flight = innerJson["mag_aligned_in_flight"].GetBool();
		_control_status.flags.mag_dec = innerJson["mag_dec"].GetBool();
		_control_status.flags.mag_fault = innerJson["mag_fault"].GetBool();
		_control_status.flags.mag_field_disturbed = innerJson["mag_field_disturbed"].GetBool();
		_control_status.flags.mag_hdg = innerJson["mag_hdg"].GetBool();
		_control_status.flags.opt_flow = innerJson["opt_flow"].GetBool();
		_control_status.flags.rng_fault = innerJson["rng_fault"].GetBool();
		_control_status.flags.rng_hgt = innerJson["rng_hgt"].GetBool();
		_control_status.flags.rng_kin_consistent = innerJson["rng_kin_consistent"].GetBool();
		_control_status.flags.rng_stuck = innerJson["rng_stuck"].GetBool();
		_control_status.flags.synthetic_mag_z = innerJson["synthetic_mag_z"].GetBool();
		_control_status.flags.tilt_align = innerJson["tilt_align"].GetBool();
		_control_status.flags.vehicle_at_rest = innerJson["vehicle_at_rest"].GetBool();
		_control_status.flags.wind = innerJson["wind"].GetBool();
		_control_status.flags.wind_dead_reckoning = innerJson["wind_dead_reckoning"].GetBool();
		_control_status.flags.yaw_align = innerJson["yaw_align"].GetBool();
}	{
		rapidjson::Value& innerJson = ekfObj["_control_status_prev"]["flags"];
		_control_status_prev.flags.baro_hgt = innerJson["baro_hgt"].GetBool();
		_control_status_prev.flags.ev_hgt = innerJson["ev_hgt"].GetBool();
		_control_status_prev.flags.ev_pos = innerJson["ev_pos"].GetBool();
		_control_status_prev.flags.ev_vel = innerJson["ev_vel"].GetBool();
		_control_status_prev.flags.ev_yaw = innerJson["ev_yaw"].GetBool();
		_control_status_prev.flags.fixed_wing = innerJson["fixed_wing"].GetBool();
		_control_status_prev.flags.fuse_aspd = innerJson["fuse_aspd"].GetBool();
		_control_status_prev.flags.fuse_beta = innerJson["fuse_beta"].GetBool();
		_control_status_prev.flags.gnd_effect = innerJson["gnd_effect"].GetBool();
		_control_status_prev.flags.gps = innerJson["gps"].GetBool();
		_control_status_prev.flags.gps_hgt = innerJson["gps_hgt"].GetBool();
		_control_status_prev.flags.gps_yaw = innerJson["gps_yaw"].GetBool();
		_control_status_prev.flags.gps_yaw_fault = innerJson["gps_yaw_fault"].GetBool();
		_control_status_prev.flags.in_air = innerJson["in_air"].GetBool();
		_control_status_prev.flags.inertial_dead_reckoning = innerJson["inertial_dead_reckoning"].GetBool();
		_control_status_prev.flags.mag_3D = innerJson["mag_3D"].GetBool();
		_control_status_prev.flags.mag_aligned_in_flight = innerJson["mag_aligned_in_flight"].GetBool();
		_control_status_prev.flags.mag_dec = innerJson["mag_dec"].GetBool();
		_control_status_prev.flags.mag_fault = innerJson["mag_fault"].GetBool();
		_control_status_prev.flags.mag_field_disturbed = innerJson["mag_field_disturbed"].GetBool();
		_control_status_prev.flags.mag_hdg = innerJson["mag_hdg"].GetBool();
		_control_status_prev.flags.opt_flow = innerJson["opt_flow"].GetBool();
		_control_status_prev.flags.rng_fault = innerJson["rng_fault"].GetBool();
		_control_status_prev.flags.rng_hgt = innerJson["rng_hgt"].GetBool();
		_control_status_prev.flags.rng_kin_consistent = innerJson["rng_kin_consistent"].GetBool();
		_control_status_prev.flags.rng_stuck = innerJson["rng_stuck"].GetBool();
		_control_status_prev.flags.synthetic_mag_z = innerJson["synthetic_mag_z"].GetBool();
		_control_status_prev.flags.tilt_align = innerJson["tilt_align"].GetBool();
		_control_status_prev.flags.vehicle_at_rest = innerJson["vehicle_at_rest"].GetBool();
		_control_status_prev.flags.wind = innerJson["wind"].GetBool();
		_control_status_prev.flags.wind_dead_reckoning = innerJson["wind_dead_reckoning"].GetBool();
		_control_status_prev.flags.yaw_align = innerJson["yaw_align"].GetBool();
}	{
		rapidjson::Value& innerJson = ekfObj["_warning_events"]["flags"];
		_warning_events.flags.bad_yaw_using_gps_course = innerJson["bad_yaw_using_gps_course"].GetBool();
		_warning_events.flags.emergency_yaw_reset_gps_yaw_stopped = innerJson["emergency_yaw_reset_gps_yaw_stopped"].GetBool();
		_warning_events.flags.emergency_yaw_reset_mag_stopped = innerJson["emergency_yaw_reset_mag_stopped"].GetBool();
		_warning_events.flags.gps_data_stopped = innerJson["gps_data_stopped"].GetBool();
		_warning_events.flags.gps_data_stopped_using_alternate = innerJson["gps_data_stopped_using_alternate"].GetBool();
		_warning_events.flags.gps_fusion_timout = innerJson["gps_fusion_timout"].GetBool();
		_warning_events.flags.gps_quality_poor = innerJson["gps_quality_poor"].GetBool();
		_warning_events.flags.height_sensor_timeout = innerJson["height_sensor_timeout"].GetBool();
		_warning_events.flags.invalid_accel_bias_cov_reset = innerJson["invalid_accel_bias_cov_reset"].GetBool();
		_warning_events.flags.stopping_mag_use = innerJson["stopping_mag_use"].GetBool();
		_warning_events.flags.stopping_navigation = innerJson["stopping_navigation"].GetBool();
		_warning_events.flags.vision_data_stopped = innerJson["vision_data_stopped"].GetBool();
}	{
		rapidjson::Value& innerJson = ekfObj["_information_events"]["flags"];
		_information_events.flags.gps_checks_passed = innerJson["gps_checks_passed"].GetBool();
		_information_events.flags.reset_pos_to_gps = innerJson["reset_pos_to_gps"].GetBool();
		_information_events.flags.reset_pos_to_last_known = innerJson["reset_pos_to_last_known"].GetBool();
		_information_events.flags.reset_pos_to_vision = innerJson["reset_pos_to_vision"].GetBool();
		_information_events.flags.reset_vel_to_flow = innerJson["reset_vel_to_flow"].GetBool();
		_information_events.flags.reset_vel_to_gps = innerJson["reset_vel_to_gps"].GetBool();
		_information_events.flags.reset_vel_to_vision = innerJson["reset_vel_to_vision"].GetBool();
		_information_events.flags.reset_vel_to_zero = innerJson["reset_vel_to_zero"].GetBool();
		_information_events.flags.starting_gps_fusion = innerJson["starting_gps_fusion"].GetBool();
		_information_events.flags.starting_vision_pos_fusion = innerJson["starting_vision_pos_fusion"].GetBool();
		_information_events.flags.starting_vision_vel_fusion = innerJson["starting_vision_vel_fusion"].GetBool();
		_information_events.flags.starting_vision_yaw_fusion = innerJson["starting_vision_yaw_fusion"].GetBool();
		_information_events.flags.yaw_aligned_to_imu_gps = innerJson["yaw_aligned_to_imu_gps"].GetBool();
}{
}
{
		_min_obs_interval_us = ekfObj["_min_obs_interval_us"].GetUint();
}
{
		_drag_sample_count = ekfObj["_drag_sample_count"].GetUint();
}
{
	if (ekfObj["_drag_sample_time_dt"].IsBool()){
		_drag_sample_time_dt = NAN;
	}else{
		_drag_sample_time_dt = ekfObj["_drag_sample_time_dt"].GetFloat();
	}
}

}
