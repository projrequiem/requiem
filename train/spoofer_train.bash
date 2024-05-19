#!/bin/bash
INNOV_SURROGATE_PATH="PATH_TO_INNOVATION_SURROGATE"
POS_SURROGATE_PATH="PATH_TO_POSITION_SURROGATE"
VEL_SURROGATE_PATH="PATH_TO_VELOCITY_SURROGATE"
DATASET_PATH="INSERT_TRAINSET_PATH_HERE"
VAL_DATASET_PATH="INSERT_VALIDATIONSET_PATH_HERE"
OUTPUT_CP_DIR="INSERT_MODEL_CHECKPOINT_HERE"
CONTINUE_DIR="INSERT_MODEL_CHECKPOINT_CONTINUATION_PATH_HERE" # Usually the same as $OUTPUT_CP_DIR
ATK_TYPE="dbm" # dbm := direction bias, nc := no correction
PARAMS=(
	-i "${DATASET_PATH}" # Collected samples
	-o "${OUTPUT_CP_DIR}" # Output checkpoint dir
	-l ./index # Directory of the lookup
	-e 100 # Epochs
	-sn test_spec # Specification
	-b 64 # Mini-batch size
	-td "${VAL_DATASET_PATH}" # Validation data set
	-dm "${INNOV_SURROGATE_PATH}"
	-emv "${VEL_SURROGATE_PATH}"
	-emp "${POS_SURROGATE_PATH}"
	-m "${ATK_TYPE}"
	# -c "${CONTINUE_DIR}" # To continue
)
python scripts/gan_train.py "${PARAMS[@]}"
