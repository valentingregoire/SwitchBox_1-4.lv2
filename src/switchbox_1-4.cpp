#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <lv2.h>

/**********************************************************************************************************************************************************/

// #define PLUGIN_URI "http://moddevices.com/plugins/mod-devel/SwitchTrigger4"
#define PLUGIN_URI "https://github.com/valentingregoire/SwitchBox_1-4.lv2"

enum {IN, OUT_1, OUT_2, OUT_3, OUT_4, ACTIVE_CHANNEL};

/**********************************************************************************************************************************************************/

class SwitchBox_1_4
{
public:
    SwitchBox_1_4() {}
    ~SwitchBox_1_4() {}
    static LV2_Handle instantiate(const LV2_Descriptor* descriptor, double samplerate, const char* bundle_path, const LV2_Feature* const* features);
    static void activate(LV2_Handle instance);
    static void deactivate(LV2_Handle instance);
    static void connect_port(LV2_Handle instance, uint32_t port, void *data);
    static void run(LV2_Handle instance, uint32_t n_samples);
    static void cleanup(LV2_Handle instance);
    static const void* extension_data(const char* uri);
    float *in;
    float *out_1;
    float *out_2;
    float *out_3;
    float *out_4;
    float *active_channel;
};

/**********************************************************************************************************************************************************/

static const LV2_Descriptor Descriptor = {
    PLUGIN_URI,
    SwitchBox_1_4::instantiate,
    SwitchBox_1_4::connect_port,
    SwitchBox_1_4::activate,
    SwitchBox_1_4::run,
    SwitchBox_1_4::deactivate,
    SwitchBox_1_4::cleanup,
    SwitchBox_1_4::extension_data
};

/**********************************************************************************************************************************************************/

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    if (index == 0) return &Descriptor;
    else return NULL;
}

/**********************************************************************************************************************************************************/

LV2_Handle SwitchBox_1_4::instantiate(const LV2_Descriptor* descriptor, double samplerate, const char* bundle_path, const LV2_Feature* const* features)
{
    return (LV2_Handle) new SwitchBox_1_4();
}

/**********************************************************************************************************************************************************/

void SwitchBox_1_4::activate(LV2_Handle instance) {}
void SwitchBox_1_4::deactivate(LV2_Handle instance) {}

/**********************************************************************************************************************************************************/

void SwitchBox_1_4::connect_port(LV2_Handle instance, uint32_t port, void *data)
{
    SwitchBox_1_4 *plugin = (SwitchBox_1_4 *) instance;
    switch (port)
    {
        case IN:             plugin->in             = (float*) data; break;
        case OUT_1:          plugin->out_1          = (float*) data; break;
        case OUT_2:          plugin->out_2          = (float*) data; break;
        case OUT_3:          plugin->out_3          = (float*) data; break;
        case OUT_4:          plugin->out_4          = (float*) data; break;
        case ACTIVE_CHANNEL: plugin->active_channel = (float*) data; break;
    }
}

/**********************************************************************************************************************************************************/

void SwitchBox_1_4::run(LV2_Handle instance, uint32_t n_samples)
{
    SwitchBox_1_4 *plugin = (SwitchBox_1_4 *) instance;

    float *in    = plugin->in;
    float *out_1 = plugin->out_1;
    float *out_2 = plugin->out_2;
    float *out_3 = plugin->out_3;
    float *out_4 = plugin->out_4;

    // active_channel is 1-4; clamp to valid range
    int channel = (int)*plugin->active_channel;
    if (channel < 1) channel = 1;
    if (channel > 4) channel = 4;

    for (uint32_t i = 0; i < n_samples; i++)
    {
        *out_1 = (channel == 1) ? *in : 0.0f;
        *out_2 = (channel == 2) ? *in : 0.0f;
        *out_3 = (channel == 3) ? *in : 0.0f;
        *out_4 = (channel == 4) ? *in : 0.0f;
        in++; out_1++; out_2++; out_3++; out_4++;
    }
}

/**********************************************************************************************************************************************************/

void SwitchBox_1_4::cleanup(LV2_Handle instance)
{
    delete ((SwitchBox_1_4 *) instance);
}

/**********************************************************************************************************************************************************/

const void* SwitchBox_1_4::extension_data(const char* uri)
{
    return NULL;
}
