/**
 * Activation AUX channel
 *
 * Controls whether the rendezvous aircraft may publish Offboard setpoints.
 * Position broadcast remains enabled while the module is running.
 *
 * @value 0 Always enabled
 * @value 1 AUX1
 * @value 2 AUX2
 * @value 3 AUX3
 * @value 4 AUX4
 * @value 5 AUX5
 * @value 6 AUX6
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_INT32(CRDZ_ACT_AUX, 3);

/**
 * Activation joystick button
 *
 * Controls whether the rendezvous aircraft may publish Offboard setpoints using
 * the MANUAL_CONTROL buttons bitmask. Button numbers match the zero-based
 * numbering shown by QGroundControl.
 *
 * @value -1 Disabled
 * @min -1
 * @max 15
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_INT32(CRDZ_ACT_BTN, -1);

/**
 * Horizontal distance from target
 *
 * Desired horizontal distance for the rendezvous aircraft relative to the
 * target aircraft. Set to 0 to track the target position without a horizontal
 * offset. Negative values keep the startup offset from -d/-x/-y.
 *
 * @unit m
 * @min -1
 * @max 100
 * @decimal 1
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_FLOAT(CRDZ_DIST, 0.f);

/**
 * Enable explicit horizontal offsets
 *
 * When enabled, CRDZ_X_OFF and CRDZ_Y_OFF directly define the target-relative
 * NED horizontal offset. CRDZ_DIST is ignored for horizontal offset generation.
 * Keep disabled to use the legacy CRDZ_DIST scaling of the startup -x/-y
 * offset direction.
 *
 * @boolean
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_INT32(CRDZ_XY_OFF_EN, 0);

/**
 * Target NED X offset
 *
 * Exact NED X offset from the target aircraft used when CRDZ_XY_OFF_EN is set.
 * Positive is North in the local NED frame.
 *
 * @unit m
 * @min -100
 * @max 100
 * @decimal 1
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_FLOAT(CRDZ_X_OFF, -5.f);

/**
 * Target NED Y offset
 *
 * Exact NED Y offset from the target aircraft used when CRDZ_XY_OFF_EN is set.
 * Positive is East in the local NED frame.
 *
 * @unit m
 * @min -100
 * @max 100
 * @decimal 1
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_FLOAT(CRDZ_Y_OFF, 0.f);

/**
 * Approach speed toward target position
 *
 * Horizontal closing speed added while the rendezvous aircraft has not reached
 * the desired target-relative position. Keep this above the target aircraft
 * speed when the follower needs to catch up.
 *
 * Set to 0 to use the startup -v argument. The final horizontal velocity is
 * limited to 50 m/s after target-velocity feed-forward is applied.
 *
 * @unit m/s
 * @min 0
 * @max 50
 * @decimal 1
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_FLOAT(CRDZ_APP_SPD, 20.f);

/**
 * Slowdown radius near target position
 *
 * The commanded closing speed scales down inside this radius. It is also
 * limited by a stopping-distance profile derived from CRDZ_VSLEW, so braking
 * starts before the aircraft reaches the target-relative position.
 *
 * @unit m
 * @min 0.5
 * @max 100
 * @decimal 1
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_FLOAT(CRDZ_SLOW_RAD, 5.f);

/**
 * Enable arrival hold
 *
 * A moving target inside the position threshold is followed using its live
 * horizontal velocity, without horizontal position feedback that could command
 * a U-turn after crossing the target point. A slow target is frozen only after
 * relative velocity is below CRDZ_HOLD_VEL for CRDZ_HOLD_T seconds. Following
 * resumes normal approach when target-relative error exceeds CRDZ_HOLD_REL.
 *
 * @boolean
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_INT32(CRDZ_HOLD_EN, 0);

/**
 * Arrival hold position mode
 *
 * Selects which position error axes must be inside their hold radius. Moving
 * target velocity following begins at this position threshold. A stationary
 * hold additionally requires relative speed below CRDZ_HOLD_VEL.
 *
 * @value 0 Horizontal and vertical
 * @value 1 Horizontal only
 * @value 2 Vertical only
 * @min 0
 * @max 2
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_INT32(CRDZ_HOLD_MODE, 0);

/**
 * Arrival hold horizontal radius
 *
 * Horizontal error threshold used before the rendezvous setpoint can be frozen.
 *
 * @unit m
 * @min 0.1
 * @max 20
 * @decimal 1
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_FLOAT(CRDZ_HOLD_HRAD, 1.5f);

/**
 * Arrival hold vertical radius
 *
 * Vertical error threshold used before the rendezvous setpoint can be frozen.
 *
 * @unit m
 * @min 0.1
 * @max 20
 * @decimal 1
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_FLOAT(CRDZ_HOLD_VRAD, 1.5f);

/**
 * Arrival relative speed threshold
 *
 * Maximum follower-to-target relative speed allowed before stationary hold.
 * This threshold also defines whether a target is slow enough for an absolute
 * setpoint freeze. Faster targets use live horizontal velocity following.
 *
 * @unit m/s
 * @min 0
 * @max 10
 * @decimal 2
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_FLOAT(CRDZ_HOLD_VEL, 0.5f);

/**
 * Arrival hold dwell time
 *
 * Time that the aircraft must stay inside the position radius selected by
 * CRDZ_HOLD_MODE before entering arrival behavior.
 *
 * @unit s
 * @min 0
 * @max 10
 * @decimal 1
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_FLOAT(CRDZ_HOLD_T, 1.f);

/**
 * Arrival hold release radius
 *
 * Distance from the frozen setpoint at which live target motion releases the
 * hold latch and normal rendezvous tracking resumes.
 *
 * @unit m
 * @min 0.1
 * @max 50
 * @decimal 1
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_FLOAT(CRDZ_HOLD_REL, 5.f);

/**
 * Horizontal velocity slew limit
 *
 * Limits how quickly the rendezvous horizontal velocity setpoint may change and
 * supplies the deceleration used by the stopping-distance approach profile.
 * Set to 0 to use the safe default of 5 m/s^2.
 *
 * @unit m/s^2
 * @min 0
 * @max 20
 * @decimal 1
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_FLOAT(CRDZ_VSLEW, 5.f);

/**
 * Target position low-pass time constant
 *
 * Applies a first-order low-pass filter to the target aircraft local NED
 * position before generating the rendezvous position and velocity setpoints.
 * This helps reject telemetry jitter that would otherwise make the follower
 * accelerate and decelerate repeatedly.
 *
 * Set to 0 to disable position filtering.
 *
 * @unit s
 * @min 0
 * @max 10
 * @decimal 2
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_FLOAT(CRDZ_TPOS_TC, 0.f);

/**
 * Target velocity low-pass time constant
 *
 * Applies a first-order low-pass filter to the target aircraft NED velocity
 * feed-forward before it is added to the rendezvous approach velocity.
 *
 * Set to 0 to disable velocity filtering.
 *
 * @unit s
 * @min 0
 * @max 10
 * @decimal 2
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_FLOAT(CRDZ_TVEL_TC, 0.f);

/**
 * Target position jump limit
 *
 * Limits one accepted target-position measurement jump before the low-pass
 * filter. This is useful when the target telemetry occasionally reports a
 * bad GPS/global position sample.
 *
 * Set to 0 to disable jump limiting.
 *
 * @unit m
 * @min 0
 * @max 200
 * @decimal 1
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_FLOAT(CRDZ_TPOS_JMP, 0.f);

/**
 * Altitude difference from target
 *
 * Desired altitude difference for the rendezvous aircraft relative to the
 * target aircraft. A positive value keeps the rendezvous aircraft above the
 * target aircraft.
 *
 * @unit m
 * @min -50
 * @max 50
 * @decimal 1
 * @group Cooperative Rendezvous
 */
PARAM_DEFINE_FLOAT(CRDZ_ALT_DIFF, 0.f);
