#ifndef CLOCK_H
#define CLOCK_H

uint8_t clock_get_mode();

/**
 * Clock get system frequency
 * 
 * @return u_int32_t
 */
u_int32_t clock_get_sys_freq_hz();

/**
 * Clock get frequency
 * 
 * @return u_int32_t
 */
u_int32_t clock_get_freq_hz();

/**
 * Clock get PWM div
 * 
 * @return u_int16_t
 */
u_int16_t clock_get_pwm_div();

/**
 * Clock get PWM wrap
 * 
 * @return u_int16_t
 */
u_int16_t clock_get_pwm_wrap();

/**
 * Clock get duty cycle
 * 
 * @return u_int16_t
 */
u_int16_t clock_get_duty_cycle();

/**
 * Clock get timer type
 * 
 * @return u_int8_t
 */
u_int8_t clock_get_timer_type();

/**
 * Clock set frequency
 * 
 * @param u_int32_t hz
 * @return void
 */
void clock_set_freq_hz(u_int32_t hz);

/**
 * Clock set PWM div
 * 
 * @param u_int16_t div
 * @return void
 */
void clock_start_pwm();

/**
 * Clock stop PWM
 * 
 * @return void
 */
void clock_stop_pwm();

/**
 * Clock start repeating timer
 * 
 * @return void
 */
void clock_start_rpt();

/**
 * Clock stop repeating timer
 * 
 * @return void
 */
void clock_stop_rpt();

/**
 * Clock pulse start
 * 
 * @return void
 */
void clock_pulse_start();

/**
 * Clock pulse stop
 * 
 * @return void
 */
void clock_pulse_stop();

/**
 * Clock step mode
 * 
 * @param bool enable
 * @return void
 */
void clock_step(bool enable);

/**
 * Clock step pulse
 * 
 * @return void
 */
void clock_step_pulse();

/**
 * Clock reset
 * 
 * @return void
 */
void clock_reset();

/**
 * Clock init function
 * 
 * @return void
 */
void clock_init();

#endif