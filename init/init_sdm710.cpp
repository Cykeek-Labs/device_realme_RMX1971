/*
 * Copyright (C) 2021 LineageOS Project
 *
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <vector>
#include <sys/sysinfo.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/strings.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::SetProperty;
using android::base::ReadFileToString;
using android::base::Trim;
using android::base::GetProperty;
using std::string;

string heapstartsize, heapgrowthlimit, heapsize,
       heapminfree, heapmaxfree, heaptargetutilization;

std::vector<string> ro_props_default_source_order = {
    "",
    "bootimage.",
    "odm.",
    "product.",
    "system.",
    "system_ext.",
    "vendor."
};

void property_override(char const prop[], char const value[], bool add = true) {
    prop_info *pi;

    pi = (prop_info *)__system_property_find(prop);

    if (pi)
	__system_property_update(pi, value, strlen(value));
    else if (add)
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void load_dalvik_properties() 
{
    struct sysinfo sys;

    sysinfo(&sys);
    if (sys.totalram > 6144ull * 1024 * 1024)
	{
		// from - phone-xxhdpi-8192-dalvik-heap.mk
                property_override("dalvik.vm.heapstartsize", "24m");
                property_override("dalvik.vm.heaptargetutilization", "0.46");
                property_override("dalvik.vm.heapgrowthlimit", "256m");
                property_override("dalvik.vm.heapsize", "512m");
	        property_override("dalvik.vm.heapmaxfree", "48m");
                property_override("dalvik.vm.heapminfree", "8m");
	}
	else if
	{
                // from - phone-xhdpi-6144-dalvik-heap.mk
		property_override("dalvik.vm.heapstartsize", "16m");
		property_override("dalvik.vm.heaptargetutilization", "0.5");
		property_override("dalvik.vm.heapgrowthlimit", "256m");
		property_override("dalvik.vm.heapsize", "512m");
		property_override("dalvik.vm.heapmaxfree", "32m");
		property_override("dalvik.vm.heapminfree", "8m");
	}
}

void vendor_load_properties()
{
    SetProperty("dalvik.vm.heaptargetutilization", heaptargetutilization);
    load_dalvik_properties();
    const auto set_ro_build_prop = [](const std::string &source,
            const std::string &prop, const std::string &value) {
        auto prop_name = "ro." + source + "build." + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    const auto set_ro_product_prop = [](const std::string &source,
            const std::string &prop, const std::string &value) {
        auto prop_name = "ro.product." + source + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    char const *operator_name_file = "/proc/oplusVersion/operatorName";
    std::string build_epoch, device, operator_name;
    build_epoch = "";

    if (ReadFileToString(operator_name_file, &operator_name)) {
        /* CHINA */
        if ((Trim(operator_name) == "")) {
        device = "RMX1971";
           property_override("ro.build.fingerprint", "qti/sdm710/sdm710:11/RKQ1.201217.002/1623376276806:user/release-keys");
           property_override("ro.build.product", device.c_str());
           property_override("ro.boot.verifiedbootstate", "green");
           for (const auto &source : ro_props_default_source_order) {
               set_ro_product_prop(source, "device", device.c_str());
               set_ro_product_prop(source, "model", device.c_str());
           }
           SetProperty("ro.separate.soft", "");
        /* FOREIGN */
        } else if ((Trim(operator_name) == "")) {
        device = "RMX1971";
           property_override("ro.build.fingerprint", "qti/sdm710/sdm710:11/RKQ1.201217.002/1623376276806:user/release-keys");
           property_override("ro.build.product", device.c_str());
           property_override("ro.boot.verifiedbootstate", "green");
           for (const auto &source : ro_props_default_source_order) {
               set_ro_product_prop(source, "device", device.c_str());
               set_ro_product_prop(source, "model", device.c_str());
           }
           SetProperty("ro.separate.soft", "");
           SetProperty("ro.com.google.clientidbase.cr", "android-oppo");
           SetProperty("ro.com.google.clientidbase.ms", "android-oppo");
        /* FOREIGN INDIA */
        } else if ((Trim(operator_name) == "")) {
        device = "RMX1971";
           property_override("ro.build.fingerprint", "qti/sdm710/sdm710:11/RKQ1.201217.002/1623376276806:user/release-keys");
           property_override("ro.build.product", device.c_str());
           property_override("ro.boot.verifiedbootstate", "green");
           for (const auto &source : ro_props_default_source_order) {
               set_ro_product_prop(source, "device", device.c_str());
               set_ro_product_prop(source, "model", device.c_str());
           }
           SetProperty("ro.separate.soft", "");
           SetProperty("ro.com.google.clientidbase.cr", "android-oppo");
           SetProperty("ro.com.google.clientidbase.ms", "android-oppo");
        /* VIETNAM_128GB */
        } else if ((Trim(operator_name) == "")) {
        device = "RMX1971";
           property_override("ro.build.fingerprint", "qti/sdm710/sdm710:11/RKQ1.201217.002/1623376276806:user/release-keys");
           property_override("ro.build.product", device.c_str());
           property_override("ro.boot.verifiedbootstate", "green");
           for (const auto &source : ro_props_default_source_order) {
               set_ro_product_prop(source, "device", device.c_str());
               set_ro_product_prop(source, "model", device.c_str());
           }
           SetProperty("ro.separate.soft", "");
           SetProperty("ro.com.google.clientidbase.cr", "android-oppo");
           SetProperty("ro.com.google.clientidbase.ms", "android-oppo");
        /* VIETNAM_64GB */
        } else if ((Trim(operator_name) == "")) {
        device = "RMX1971";
           property_override("ro.build.fingerprint", "qti/sdm710/sdm710:11/RKQ1.201217.002/1623376276806:user/release-keys");
           property_override("ro.build.product", device.c_str());
           property_override("ro.boot.verifiedbootstate", "green");
           for (const auto &source : ro_props_default_source_order) {
               set_ro_product_prop(source, "device", device.c_str());
               set_ro_product_prop(source, "model", device.c_str());
           }
           SetProperty("ro.separate.soft", "");
           SetProperty("ro.com.google.clientidbase.cr", "android-oppo");
           SetProperty("ro.com.google.clientidbase.ms", "android-oppo");
        /* FOREIGN EUROPE*/
        } else if ((Trim(operator_name) == "")) {
        device = "RMX1971";
           property_override("ro.build.fingerprint", "qti/sdm710/sdm710:11/RKQ1.201217.002/1623376276806:user/release-keys");
           property_override("ro.build.product", device.c_str());
           property_override("ro.boot.verifiedbootstate", "green");
           for (const auto &source : ro_props_default_source_order) {
               set_ro_product_prop(source, "device", device.c_str());
               set_ro_product_prop(source, "model", device.c_str());
           }
           SetProperty("ro.separate.soft", "");
           SetProperty("ro.com.google.clientidbase.cr", "android-oppo");
           SetProperty("ro.com.google.clientidbase.ms", "android-oppo");
        } else {
        LOG(ERROR) << "Unsupported variant";
        }
    property_override("ro.apex.updatable", "false");
    }
}
