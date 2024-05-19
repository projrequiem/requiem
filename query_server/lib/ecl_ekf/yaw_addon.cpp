#include "EKFGSF_yaw.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/filereadstream.h>
void EKFGSF_yaw::toJson(rapidjson::Value & ekfObj, rapidjson::Document::AllocatorType & allocator){
{
}
{
	{
		rapidjson::Value array_delta_ang(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_delta_ang.PushBack(_delta_ang(i), allocator);
		}
		ekfObj.AddMember("_delta_ang", array_delta_ang, allocator);
	}
}
{
	{
		rapidjson::Value array_delta_vel(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_delta_vel.PushBack(_delta_vel(i), allocator);
		}
		ekfObj.AddMember("_delta_vel", array_delta_vel, allocator);
	}
}
{
	if (isnan(_delta_ang_dt)){
		ekfObj.AddMember("_delta_ang_dt", false, allocator);
	}else{
		ekfObj.AddMember("_delta_ang_dt", _delta_ang_dt, allocator);
	}
}
{
	if (isnan(_delta_vel_dt)){
		ekfObj.AddMember("_delta_vel_dt", false, allocator);
	}else{
		ekfObj.AddMember("_delta_vel_dt", _delta_vel_dt, allocator);
	}
}
{
	if (isnan(_true_airspeed)){
		ekfObj.AddMember("_true_airspeed", false, allocator);
	}else{
		ekfObj.AddMember("_true_airspeed", _true_airspeed, allocator);
	}
}
{
	if (isnan(_ahrs_ekf_gsf_tilt_aligned)){
		ekfObj.AddMember("_ahrs_ekf_gsf_tilt_aligned", false, allocator);
	}else{
		ekfObj.AddMember("_ahrs_ekf_gsf_tilt_aligned", _ahrs_ekf_gsf_tilt_aligned, allocator);
	}
}
{
	if (isnan(_ahrs_accel_fusion_gain)){
		ekfObj.AddMember("_ahrs_accel_fusion_gain", false, allocator);
	}else{
		ekfObj.AddMember("_ahrs_accel_fusion_gain", _ahrs_accel_fusion_gain, allocator);
	}
}
{
	{
		rapidjson::Value array_ahrs_accel(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_ahrs_accel.PushBack(_ahrs_accel(i), allocator);
		}
		ekfObj.AddMember("_ahrs_accel", array_ahrs_accel, allocator);
	}
}
{
	if (isnan(_ahrs_accel_norm)){
		ekfObj.AddMember("_ahrs_accel_norm", false, allocator);
	}else{
		ekfObj.AddMember("_ahrs_accel_norm", _ahrs_accel_norm, allocator);
	}
}
{
	if (isnan(_vel_data_updated)){
		ekfObj.AddMember("_vel_data_updated", false, allocator);
	}else{
		ekfObj.AddMember("_vel_data_updated", _vel_data_updated, allocator);
	}
}
{
	if (isnan(_run_ekf_gsf)){
		ekfObj.AddMember("_run_ekf_gsf", false, allocator);
	}else{
		ekfObj.AddMember("_run_ekf_gsf", _run_ekf_gsf, allocator);
	}
}
{
	{
		rapidjson::Value array_vel_NE(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_vel_NE.PushBack(_vel_NE(i), allocator);
		}
		ekfObj.AddMember("_vel_NE", array_vel_NE, allocator);
	}
}
{
	if (isnan(_vel_accuracy)){
		ekfObj.AddMember("_vel_accuracy", false, allocator);
	}else{
		ekfObj.AddMember("_vel_accuracy", _vel_accuracy, allocator);
	}
}
{
	if (isnan(_ekf_gsf_vel_fuse_started)){
		ekfObj.AddMember("_ekf_gsf_vel_fuse_started", false, allocator);
	}else{
		ekfObj.AddMember("_ekf_gsf_vel_fuse_started", _ekf_gsf_vel_fuse_started, allocator);
	}
}
{
	if (isnan(_gsf_yaw)){
		ekfObj.AddMember("_gsf_yaw", false, allocator);
	}else{
		ekfObj.AddMember("_gsf_yaw", _gsf_yaw, allocator);
	}
}
{
	if (isnan(_gsf_yaw_variance)){
		ekfObj.AddMember("_gsf_yaw_variance", false, allocator);
	}else{
		ekfObj.AddMember("_gsf_yaw_variance", _gsf_yaw_variance, allocator);
	}
}
	{
		rapidjson::Value buffArray(rapidjson::kArrayType);
		for(int index = 0; index < 5; index++){
			_ahrs_ekf_gsf_struct & elem = _ahrs_ekf_gsf[index];
			{
				rapidjson::Value structObj(rapidjson::kObjectType);
				structObj.SetObject();
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						for(int j = 0; j < 3; j++){
							arrayelem.PushBack(elem.R(i, j), allocator);
						}
					}
					structObj.AddMember("R", arrayelem, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						arrayelem.PushBack(elem.gyro_bias(i), allocator);
					}
					structObj.AddMember("gyro_bias", arrayelem, allocator);
				}
				if (isnan(elem.aligned)){
					structObj.AddMember("aligned", false, allocator);
				}else{
					structObj.AddMember("aligned", elem.aligned, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 2; i++){
						arrayelem.PushBack(elem.vel_NE[i], allocator);
					}
					structObj.AddMember("vel_NE", arrayelem, allocator);
				}
				if (isnan(elem.fuse_gps)){
					structObj.AddMember("fuse_gps", false, allocator);
				}else{
					structObj.AddMember("fuse_gps", elem.fuse_gps, allocator);
				}
				if (isnan(elem.accel_dt)){
					structObj.AddMember("accel_dt", false, allocator);
				}else{
					structObj.AddMember("accel_dt", elem.accel_dt, allocator);
				}
				buffArray.PushBack(structObj, allocator);
			}
			}
			ekfObj.AddMember("_ahrs_ekf_gsf", buffArray, allocator);	}
	{
		rapidjson::Value buffArray(rapidjson::kArrayType);
		for(int index = 0; index < 5; index++){
			_ekf_gsf_struct & elem = _ekf_gsf[index];
			{
				rapidjson::Value structObj(rapidjson::kObjectType);
				structObj.SetObject();
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						arrayelem.PushBack(elem.X(i), allocator);
					}
					structObj.AddMember("X", arrayelem, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 3; i++){
						for(int j = 0; j < 3; j++){
							arrayelem.PushBack(elem.P(i, j), allocator);
						}
					}
					structObj.AddMember("P", arrayelem, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 2; i++){
						for(int j = 0; j < 2; j++){
							arrayelem.PushBack(elem.S_inverse(i, j), allocator);
						}
					}
					structObj.AddMember("S_inverse", arrayelem, allocator);
				}
				if (isnan(elem.S_det_inverse)){
					structObj.AddMember("S_det_inverse", false, allocator);
				}else{
					structObj.AddMember("S_det_inverse", elem.S_det_inverse, allocator);
				}
				{
					rapidjson::Value arrayelem(rapidjson::kArrayType);
					for(int i = 0; i < 2; i++){
						arrayelem.PushBack(elem.innov(i), allocator);
					}
					structObj.AddMember("innov", arrayelem, allocator);
				}
				buffArray.PushBack(structObj, allocator);
			}
			}
			ekfObj.AddMember("_ekf_gsf", buffArray, allocator);	}
{
	{
		rapidjson::Value array_model_weights(rapidjson::kArrayType);
		for(int i = 0; i < 5; i++){
			array_model_weights.PushBack(_model_weights(i), allocator);
		}
		ekfObj.AddMember("_model_weights", array_model_weights, allocator);
	}
}

}
void EKFGSF_yaw::checkJson(rapidjson::Value & ekfObj){
		assert(ekfObj.HasMember("_delta_ang"));
assert(ekfObj["_delta_ang"].IsArray());
	assert(ekfObj.HasMember("_delta_vel"));
assert(ekfObj["_delta_vel"].IsArray());
	assert(ekfObj.HasMember("_delta_ang_dt"));
assert(ekfObj["_delta_ang_dt"].IsFloat() || ekfObj["_delta_ang_dt"].IsBool());
	assert(ekfObj.HasMember("_delta_vel_dt"));
assert(ekfObj["_delta_vel_dt"].IsFloat() || ekfObj["_delta_vel_dt"].IsBool());
	assert(ekfObj.HasMember("_true_airspeed"));
assert(ekfObj["_true_airspeed"].IsFloat() || ekfObj["_true_airspeed"].IsBool());
	assert(ekfObj.HasMember("_ahrs_ekf_gsf_tilt_aligned"));
assert(ekfObj["_ahrs_ekf_gsf_tilt_aligned"].IsBool());
	assert(ekfObj.HasMember("_ahrs_accel_fusion_gain"));
assert(ekfObj["_ahrs_accel_fusion_gain"].IsFloat() || ekfObj["_ahrs_accel_fusion_gain"].IsBool());
	assert(ekfObj.HasMember("_ahrs_accel"));
assert(ekfObj["_ahrs_accel"].IsArray());
	assert(ekfObj.HasMember("_ahrs_accel_norm"));
assert(ekfObj["_ahrs_accel_norm"].IsFloat() || ekfObj["_ahrs_accel_norm"].IsBool());
	assert(ekfObj.HasMember("_vel_data_updated"));
assert(ekfObj["_vel_data_updated"].IsBool());
	assert(ekfObj.HasMember("_run_ekf_gsf"));
assert(ekfObj["_run_ekf_gsf"].IsBool());
	assert(ekfObj.HasMember("_vel_NE"));
assert(ekfObj["_vel_NE"].IsArray());
	assert(ekfObj.HasMember("_vel_accuracy"));
assert(ekfObj["_vel_accuracy"].IsFloat() || ekfObj["_vel_accuracy"].IsBool());
	assert(ekfObj.HasMember("_ekf_gsf_vel_fuse_started"));
assert(ekfObj["_ekf_gsf_vel_fuse_started"].IsBool());
	assert(ekfObj.HasMember("_gsf_yaw"));
assert(ekfObj["_gsf_yaw"].IsFloat() || ekfObj["_gsf_yaw"].IsBool());
	assert(ekfObj.HasMember("_gsf_yaw_variance"));
assert(ekfObj["_gsf_yaw_variance"].IsFloat() || ekfObj["_gsf_yaw_variance"].IsBool());
{
	assert(ekfObj["_ahrs_ekf_gsf[5]"].IsObject());
	assert(ekfObj["_ahrs_ekf_gsf[5]"]["R"].IsArray());
	assert(ekfObj["_ahrs_ekf_gsf[5]"]["gyro_bias"].IsArray());
	assert(ekfObj["_ahrs_ekf_gsf[5]"]["aligned"].IsBool());
	assert(ekfObj["_ahrs_ekf_gsf[5]"]["vel_NE"].IsArray());
	assert(ekfObj["_ahrs_ekf_gsf[5]"]["fuse_gps"].IsBool());
	assert(ekfObj["_ahrs_ekf_gsf[5]"]["accel_dt"].IsFloat() || ekfObj["_ahrs_ekf_gsf[5]"]["accel_dt"].IsBool());
}
{
	assert(ekfObj["_ekf_gsf[5]"].IsObject());
	assert(ekfObj["_ekf_gsf[5]"]["X"].IsArray());
	assert(ekfObj["_ekf_gsf[5]"]["P"].IsArray());
	assert(ekfObj["_ekf_gsf[5]"]["S_inverse"].IsArray());
	assert(ekfObj["_ekf_gsf[5]"]["S_det_inverse"].IsFloat() || ekfObj["_ekf_gsf[5]"]["S_det_inverse"].IsBool());
	assert(ekfObj["_ekf_gsf[5]"]["innov"].IsArray());
}
	assert(ekfObj.HasMember("_model_weights"));
assert(ekfObj["_model_weights"].IsArray());

}
void EKFGSF_yaw::fromJson(rapidjson::Value & ekfObj){
{
	for(int i = 0; i < 3; i++){
		_delta_ang(i) = ekfObj["_delta_ang"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_delta_vel(i) = ekfObj["_delta_vel"][i].GetFloat();
	}
}
{
	if (ekfObj["_delta_ang_dt"].IsBool()){
		_delta_ang_dt = NAN;
	}else{
		_delta_ang_dt = ekfObj["_delta_ang_dt"].GetFloat();
	}
}
{
	if (ekfObj["_delta_vel_dt"].IsBool()){
		_delta_vel_dt = NAN;
	}else{
		_delta_vel_dt = ekfObj["_delta_vel_dt"].GetFloat();
	}
}
{
	if (ekfObj["_true_airspeed"].IsBool()){
		_true_airspeed = NAN;
	}else{
		_true_airspeed = ekfObj["_true_airspeed"].GetFloat();
	}
}
{
		_ahrs_ekf_gsf_tilt_aligned = ekfObj["_ahrs_ekf_gsf_tilt_aligned"].GetBool();
}
{
	if (ekfObj["_ahrs_accel_fusion_gain"].IsBool()){
		_ahrs_accel_fusion_gain = NAN;
	}else{
		_ahrs_accel_fusion_gain = ekfObj["_ahrs_accel_fusion_gain"].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_ahrs_accel(i) = ekfObj["_ahrs_accel"][i].GetFloat();
	}
}
{
	if (ekfObj["_ahrs_accel_norm"].IsBool()){
		_ahrs_accel_norm = NAN;
	}else{
		_ahrs_accel_norm = ekfObj["_ahrs_accel_norm"].GetFloat();
	}
}
{
		_vel_data_updated = ekfObj["_vel_data_updated"].GetBool();
}
{
		_run_ekf_gsf = ekfObj["_run_ekf_gsf"].GetBool();
}
{
	for(int i = 0; i < 2; i++){
		_vel_NE(i) = ekfObj["_vel_NE"][i].GetFloat();
	}
}
{
	if (ekfObj["_vel_accuracy"].IsBool()){
		_vel_accuracy = NAN;
	}else{
		_vel_accuracy = ekfObj["_vel_accuracy"].GetFloat();
	}
}
{
		_ekf_gsf_vel_fuse_started = ekfObj["_ekf_gsf_vel_fuse_started"].GetBool();
}
{
	if (ekfObj["_gsf_yaw"].IsBool()){
		_gsf_yaw = NAN;
	}else{
		_gsf_yaw = ekfObj["_gsf_yaw"].GetFloat();
	}
}
{
	if (ekfObj["_gsf_yaw_variance"].IsBool()){
		_gsf_yaw_variance = NAN;
	}else{
		_gsf_yaw_variance = ekfObj["_gsf_yaw_variance"].GetFloat();
	}
}
{
	auto & buffArray = ekfObj["_ahrs_ekf_gsf"];
	for(unsigned int index = 0; index < buffArray.Size(); index++){
		auto & elem = buffArray[index];
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					_ahrs_ekf_gsf[index].R(i, j) = elem["R"][i*3 + j].GetFloat();
				}
			}
			for(int i = 0; i < 3; i++){
				_ahrs_ekf_gsf[index].gyro_bias(i) = elem["gyro_bias"][i].GetFloat();
			}
				_ahrs_ekf_gsf[index].aligned = elem["aligned"].GetBool();
			for(int i = 0; i < 2; i++){
				if(elem["vel_NE"][i].IsBool()){
					_ahrs_ekf_gsf[index].vel_NE[i] = NAN;
				}else {
					_ahrs_ekf_gsf[index].vel_NE[i] = elem["vel_NE"][i].GetFloat();
				}
			}
				_ahrs_ekf_gsf[index].fuse_gps = elem["fuse_gps"].GetBool();
			if (elem["accel_dt"].IsBool()){
				_ahrs_ekf_gsf[index].accel_dt = NAN;
			}else{
				_ahrs_ekf_gsf[index].accel_dt = elem["accel_dt"].GetFloat();
			}
	}
}
{
	auto & buffArray = ekfObj["_ekf_gsf"];
	for(unsigned int index = 0; index < buffArray.Size(); index++){
		auto & elem = buffArray[index];
			for(int i = 0; i < 3; i++){
				_ekf_gsf[index].X(i) = elem["X"][i].GetFloat();
			}
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					_ekf_gsf[index].P(i, j) = elem["P"][i*3 + j].GetFloat();
				}
			}
			for(int i = 0; i < 2; i++){
				for(int j = 0; j < 2; j++){
					_ekf_gsf[index].S_inverse(i, j) = elem["S_inverse"][i*2 + j].GetFloat();
				}
			}
			if (elem["S_det_inverse"].IsBool()){
				_ekf_gsf[index].S_det_inverse = NAN;
			}else{
				_ekf_gsf[index].S_det_inverse = elem["S_det_inverse"].GetFloat();
			}
			for(int i = 0; i < 2; i++){
				_ekf_gsf[index].innov(i) = elem["innov"][i].GetFloat();
			}
	}
}
{
	for(int i = 0; i < 5; i++){
		_model_weights(i) = ekfObj["_model_weights"][i].GetFloat();
	}
}

}
