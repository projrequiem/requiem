yawEstimatorType ={
        "_delta_ang":["float", "float","float"],
        "_delta_vel":["float", "float","float"],
        "_delta_ang_dt": "float",
        "_delta_vel_dt": "float",
        "_true_airspeed": "float",
        "_ahrs_ekf_gsf":[
            {
                "R": ["float", "float","float","float", "float","float","float", "float","float"],
                "gyro_bias": ["float", "float","float"],
                "aligned": "bool",
                "vel_NE": ["float", "float"],
                "fuse_gps": "bool",
                "accel_dt": "float"
            },
            {
                "R": ["float", "float","float","float", "float","float","float", "float","float"],
                "gyro_bias": ["float", "float","float"],
                "aligned": "bool",
                "vel_NE": ["float", "float"],
                "fuse_gps": "bool",
                "accel_dt": "float"
            },
            {
                "R": ["float", "float","float","float", "float","float","float", "float","float"],
                "gyro_bias": ["float", "float","float"],
                "aligned": "bool",
                "vel_NE": ["float", "float"],
                "fuse_gps": "bool",
                "accel_dt": "float"
            },
            {
                "R": ["float", "float","float","float", "float","float","float", "float","float"],
                "gyro_bias": ["float", "float","float"],
                "aligned": "bool",
                "vel_NE": ["float", "float"],
                "fuse_gps": "bool",
                "accel_dt": "float"
            },
            {
                "R": ["float", "float","float","float", "float","float","float", "float","float"],
                "gyro_bias": ["float", "float","float"],
                "aligned": "bool",
                "vel_NE": ["float", "float"],
                "fuse_gps": "bool",
                "accel_dt": "float"
            }
        ],
        "_ahrs_ekf_gsf_tilt_aligned": "bool", 
        "_ahrs_accel_fusion_gain": "float",
        "_ahrs_accel": ["float", "float", "float"],
        "_ahrs_accel_norm": "float",
        "_ekf_gsf":[
            {
                "X":["float","float","float"],
                "P":["float","float","float","float","float","float","float","float","float"],
                "S_inverse":["float","float","float","float"],
                "S_det_inverse":"float",
                "innov":["float","float"]
            },
            {
                "X":["float","float","float"],
                "P":["float","float","float","float","float","float","float","float","float"],
                "S_inverse":["float","float","float","float"],
                "S_det_inverse":"float",
                "innov":["float","float"]
            },
            {
                "X":["float","float","float"],
                "P":["float","float","float","float","float","float","float","float","float"],
                "S_inverse":["float","float","float","float"],
                "S_det_inverse":"float",
                "innov":["float","float"]
            },
            {
                "X":["float","float","float"],
                "P":["float","float","float","float","float","float","float","float","float"],
                "S_inverse":["float","float","float","float"],
                "S_det_inverse":"float",
                "innov":["float","float"]
            },
            {
                "X":["float","float","float"],
                "P":["float","float","float","float","float","float","float","float","float"],
                "S_inverse":["float","float","float","float"],
                "S_det_inverse":"float",
                "innov":["float","float"]
            }
        ],
        "_vel_data_updated":"bool",
        "_run_ekf_gsf":"bool",
        "_vel_NE":["float","float"],
        "_vel_accuracy":"float",
        "_ekf_gsf_vel_fuse_started":"bool",
        "_model_weights":["float","float","float","float","float"],
        "_gsf_yaw":"float",
        "_gsf_yaw_variance":"float"
    }
    

def yaw_est_content_filter(content, n_models=5):
    output = []
    for l in content.split(';'):
        if 'struct' in l or "N_MODELS_EKFGSF" in l:
            continue
        else:
            if len(l.strip()) > 1:
                output.append(l.strip()+";")
    output.append('_ahrs_ekf_gsf_struct _ahrs_ekf_gsf[{n}];'.format(n=n_models))
    output.append('_ekf_gsf_struct _ekf_gsf[{n}];'.format(n=n_models))
    output.append('Vector{n}f _model_weights;'.format(n=n_models))
    return '\n'.join(output)