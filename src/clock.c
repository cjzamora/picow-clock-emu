#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "clock.h"

/**
 * Pulse GPIO pin
 * 
 * @var int
 */
const int PULSE_PIN = 16;

/**
 * Clock GPIO pin
 * 
 * @var int
 */
const int CLOCK_PIN = 17;

/**
 * Clock started
 * 
 * @var bool
 */
bool clock_started = false;

/**
 * Clock mode
 * 
 * 0 = astable
 * 1 = monostable
 * 
 * @var u_int8_t
 */
u_int8_t clock_mode = 0;

/**
 * Clock frequency
 * 
 * @var u_int32_t
 */
u_int32_t clock_freq_hz = CLOCK_DEF_FREQ_HZ;

/**
 * Clock PWM div
 * 
 * @var u_int16_t
 */
u_int16_t clock_pwm_div = 0;

/**
 * Clock PWM wrap
 * 
 * @var u_int16_t
 */
u_int16_t clock_pwm_wrap = 0;

/**
 * Clock duty cycle
 * 
 * @var u_int16_t
 */
u_int16_t clock_duty_cycle = 50;

/**
 * Clock timer type
 * 
 * 0 = repeating timer
 * 1 = pulse width modulation
 * 
 * @var u_int8_t
 */
u_int8_t clock_timer_type = 0;

/**
 * Clock repeating timer
 * 
 * @var struct repeating_timer
 */
struct repeating_timer clock_timer;

/**
 * Clock get mode
 * 
 * @return u_int8_t
 */
u_int8_t clock_get_mode()
{
    return clock_mode;
}

/**
 * Clock get system frequency
 * 
 * @return u_int32_t
 */
u_int32_t clock_get_sys_freq_hz()
{
    return clock_get_hz(clk_sys);
}

/**
 * Clock get frequency
 * 
 * @return u_int32_t
 */
u_int32_t clock_get_freq_hz()
{
    return clock_freq_hz;
}

/**
 * Clock get PWM div
 * 
 * @return u_int16_t
 */
u_int16_t clock_get_pwm_div()
{
    return clock_pwm_div;
}

/**
 * Clock get PWM wrap
 * 
 * @return u_int16_t
 */
u_int16_t clock_get_pwm_wrap()
{
    return clock_pwm_wrap;
}

/**
 * Clock get duty cycle
 * 
 * @return u_int16_t
 */
u_int16_t clock_get_duty_cycle()
{
    return clock_duty_cycle;
}

/**
 * Clock get timer type
 * 
 * @return u_int8_t
 */
u_int8_t clock_get_timer_type()
{
    return clock_timer_type;
}

/**
 * Clock set frequency
 * 
 * @param u_int32_t hz
 * @return void
 */
void clock_set_freq_hz(u_int32_t hz)
{
    clock_freq_hz = hz;

    clock_pulse_stop();
    clock_pulse_start();
}

/**
 * Clock set PWM configuration
 * 
 * @param u_int8_t slice_num
 * @param u_int8_t channel
 * @return void
 */
void clock_set_pwm(u_int8_t slice_num, u_int8_t channel)
{
    clock_pwm_div = ceil((float) clock_get_sys_freq_hz() / (4096 * clock_freq_hz) / 16);
    clock_pwm_wrap = clock_get_sys_freq_hz() / clock_pwm_div / clock_freq_hz;

    pwm_set_clkdiv(slice_num, clock_pwm_div);
    pwm_set_wrap(slice_num, clock_pwm_wrap);
    pwm_set_chan_level(slice_num, channel, clock_pwm_wrap / 2);
    pwm_set_enabled(slice_num, true);
}

/**
 * Clock start PWM
 * 
 * @return void
 */
void clock_start_pwm()
{
    gpio_set_function(PULSE_PIN, GPIO_FUNC_PWM);
    gpio_set_function(CLOCK_PIN, GPIO_FUNC_PWM);

    clock_set_pwm(pwm_gpio_to_slice_num(PULSE_PIN), pwm_gpio_to_channel(PULSE_PIN));
    clock_set_pwm(pwm_gpio_to_slice_num(CLOCK_PIN), pwm_gpio_to_channel(CLOCK_PIN));

    clock_timer_type = CLOCK_TIMER_PWM;
}

/**
 * Clock stop PWM
 * 
 * @return void
 */
void clock_stop_pwm()
{
    pwm_set_enabled(pwm_gpio_to_slice_num(PULSE_PIN), false);
    pwm_set_enabled(pwm_gpio_to_slice_num(CLOCK_PIN), false);
}

/**
 * Clock repeating timer callback
 * 
 * @param struct repeating_timer *t
 * @return bool
 */
bool clock_rpt_timer_callback(struct repeating_timer *t)
{
    static bool state = false;
    state = !state;

    if (state) {
        gpio_put(CLOCK_PIN, 1);
        gpio_put(PULSE_PIN, 1);

        if (clock_mode == CLOCK_MONOSTABLE) {
            return false;
        }
    } else {
        gpio_put(CLOCK_PIN, 0);
        gpio_put(PULSE_PIN, 0);
    }

    return true;
}

/**
 * Clock start repeating timer
 * 
 * @return void
 */
void clock_start_rpt()
{
    gpio_init(CLOCK_PIN);
    gpio_set_dir(CLOCK_PIN, GPIO_OUT);

    gpio_init(PULSE_PIN);
    gpio_set_dir(PULSE_PIN, GPIO_OUT);

    int ms = 1000 / clock_freq_hz;
    if (clock_mode == CLOCK_MONOSTABLE) {
        ms = 50;
    }

    add_repeating_timer_ms(ms, clock_rpt_timer_callback, NULL, &clock_timer);

    clock_timer_type = CLOCK_TIMER_RPT;
}

/**
 * Clock stop repeating timer
 * 
 * @return void
 */
void clock_stop_rpt()
{
    cancel_repeating_timer(&clock_timer);   
}

/**
 * Clock pulse start
 * 
 * @return void
 */
void clock_pulse_start()
{
    if (clock_started) {
        return;
    }

    if (clock_freq_hz < 10) {
        clock_start_rpt();
    } else {
        clock_start_pwm();
    }

    clock_started = true;
}

/**
 * Clock pulse stop
 * 
 * @return void
 */
void clock_pulse_stop()
{
    clock_stop_pwm();
    clock_stop_rpt();

    clock_started = false;
}

/**
 * Clock step mode
 * 
 * @param bool enable
 * @return void
 */
void clock_step(bool enable)
{
    if (enable) {
        clock_mode = CLOCK_MONOSTABLE;
        clock_pulse_stop();
    } else {
        clock_mode = CLOCK_ASTABLE;
        clock_pulse_start();
    }
}

/**
 * Clock pulse step
 * 
 * @return void
 */
void clock_step_pulse()
{
    clock_start_rpt();
}

/**
 * Clock reset
 * 
 * @return void
 */
void clock_reset()
{
    clock_started = false;
    clock_freq_hz = CLOCK_DEF_FREQ_HZ;
    clock_pwm_div = 0;
    clock_pwm_wrap = 0;
    clock_timer_type = CLOCK_ASTABLE;

    clock_stop_pwm();
    clock_stop_rpt();

    clock_pulse_start();
}

/**
 * Clock init function
 * 
 * @return void
 */
void clock_init()
{
    // start clock pulse
    clock_pulse_start();
}