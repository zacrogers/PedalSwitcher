#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
LOG_MODULE_REGISTER(main_mayne, LOG_LEVEL_DBG);

#include <cstdint>
#include "etl/string.h"

class ShiftRegister
{
public:
    enum class Width { B_8, B_16, B_24, B_32 };

    ShiftRegister(Width width)
    {

        init_gpio();
    }
    ~ShiftRegister()
    {}

    void set(const std::uint32_t& val)
    {
        LOG_WRN("S: 0x%08x", val);
        // gpio_pin_set_dt(&out_enable_pin, 0);
        gpio_pin_set_dt(&latch_pin, 0);

        k_msleep(100);

        for(std::uint8_t bit = get_width(); bit > 0; bit--)
        {
            gpio_pin_set_dt(&clock_pin, 0);

            if(val & (0x01 << (bit - 1)))
            {
                gpio_pin_set_dt(&data_pin, 1);
            }
            else
            {
                gpio_pin_set_dt(&data_pin, 0);
            }

            k_msleep(50);

            gpio_pin_set_dt(&clock_pin, 1);
            k_msleep(50);
        }

        gpio_pin_set_dt(&latch_pin, 1);
        // gpio_pin_set_dt(&out_enable_pin, 1);
    }

    const std::uint8_t get_width()
    {
        switch (width)
        {
        case Width::B_8:
            return 8;
            break;
        case Width::B_16:
            return 16;
            break;
        case Width::B_24:
            return 24;
            break;
        case Width::B_32:
            return 32;
            break;

        default:
            break;
        }

        return 8;
    }

private:
    Width width { Width::B_8 };

    void init_gpio()
    {
        if (!gpio_is_ready_dt(&latch_pin)) {
            // return 0;
        }

        int ret = gpio_pin_configure_dt(&latch_pin, GPIO_OUTPUT_ACTIVE);
        LOG_INF("RET: %d", ret);
        if (ret < 0) {
            // return 0;
        }
        if (!gpio_is_ready_dt(&data_pin)) {
            // return 0;
        }

        ret = gpio_pin_configure_dt(&data_pin, GPIO_OUTPUT_ACTIVE);
        LOG_INF("RET: %d", ret);
        if (ret < 0) {
            // return 0;
        }
        if (!gpio_is_ready_dt(&clock_pin)) {
            // return 0;
        }

        ret = gpio_pin_configure_dt(&clock_pin, GPIO_OUTPUT_ACTIVE);
        LOG_INF("RET: %d", ret);
        if (ret < 0) {
            // return 0;
        }
    }

    struct gpio_dt_spec latch_pin      = GPIO_DT_SPEC_GET(DT_NODELABEL(sr_latch),      gpios);
    struct gpio_dt_spec data_pin       = GPIO_DT_SPEC_GET(DT_NODELABEL(sr_data),       gpios);
    struct gpio_dt_spec clear_pin      = GPIO_DT_SPEC_GET(DT_NODELABEL(sr_clear),      gpios);
    struct gpio_dt_spec clock_pin      = GPIO_DT_SPEC_GET(DT_NODELABEL(sr_clock),      gpios);
    struct gpio_dt_spec out_enable_pin = GPIO_DT_SPEC_GET(DT_NODELABEL(sr_out_enable), gpios);
};


constexpr std::uint8_t patch_name_len { 20 };


template<std::uint8_t n_channels>
struct patch{
    etl::string<patch_name_len> name;
    etl::string<patch_name_len> channel_name[n_channels];
    std::uint8_t                mapping[n_channels];
    bool                        muted[n_channels];
    // std::uint8_t                trim[n_channels]; TODO: Add digital pots

    // constexpr std::uint8_t json_len()
    // {
    //     return (patch_name_len*(n_channels+1))+n_channels;
    // }

    // etl::string<(patch_name_len*(n_channels+1))+n_channels> to_json()
    // {

    // }
};


template<std::uint8_t n_channels> // TODO: Add check for normal range
class PedalSwitcher
{
public:
    PedalSwitcher(){}
    ~PedalSwitcher(){}

    bool load_patch(){return true;}
    bool save_patch(){return true;}

    bool set_channel(std::uint8_t channel, std::uint8_t send_to)
    {
        if((send_to > n_channels-1) || (channel > n_channels-1))
        {
            return false;
        }

        current_patch.mapping[channel] = send_to;

        std::uint32_t val { 0 };
        auto WIDTH        { 24 };
        auto mux_n_bits   { 3 };
        auto mask         { 0x07 };
        auto bit_offset   { 0 };

        // for(std::uint8_t c = 0; c < n_channels; ++c)
        // {
        //     val |= ((current_patch.mapping[c] & mask) << (bit_offset+=mux_n_bits));
        // }
        val = send_to;

        LOG_INF("Val: 0x%08x", val);

        shift_reg.set(val);


        return true;
    }
    // void mute_channel(); TODO: Wire up the INH pin on next revision

private:
    struct patch<n_channels> current_patch { };
    ShiftRegister     shift_reg     { ShiftRegister::Width::B_8 };

};


constexpr std::uint8_t n_channels { 8 };


int main(void)
{
    LOG_INF("Starting");
    PedalSwitcher<n_channels> switcher { };

	while (1)
	{
        for(std::uint8_t i = 0; i < n_channels; ++i)
        {
            for(std::uint8_t j = 0; j < n_channels; ++j)
            {
                switcher.set_channel(i, j);
                LOG_INF("From: %d, To: %d", i, j);
                k_msleep(1000);
            }
        }
	}
	return 0;
}