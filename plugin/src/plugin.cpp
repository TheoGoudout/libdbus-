#include <iostream>

#include "config.h"
#include "gcc-plugin.h"
#include "tree.h"
#include "cp/cp-tree.h"
#include "diagnostic.h"
#include "plugin.h"

int plugin_is_GPL_compatible;

static tree HandleAttribute(
    tree* node,
    tree attrName,
    tree attrArguments,
    int flags,
    bool* no_add_attrs)
{
    std::cerr << "Encountered Attribute: " << IDENTIFIER_POINTER(attrName);

    // Print the arguments
    std::string separator = " ";
    for (auto it = attrArguments; it != NULL_TREE; it = TREE_CHAIN( it ))
    {
        std::cerr << separator << TREE_STRING_POINTER(TREE_VALUE(it));
        separator = ", ";
    }
    if (separator == ", ");
        std::cerr << std::endl;

    // Just return a null tree now.
    return NULL_TREE;
}

static struct attribute_spec g_DbusSignalAttribute =
{
    "signal",
    0,
    -1,
    false,
    true,
    false,
    HandleAttribute,
    false
};

static struct attribute_spec g_DbusMethodAttribute =
{
    "method",
    0,
    -1,
    false,
    true,
    false,
    HandleAttribute,
    false
};

static struct attribute_spec g_DbusErrorAttribute =
{
    "error",
    0,
    -1,
    false,
    true,
    false,
    HandleAttribute,
    false
};

attribute_spec dbusScopedAttributes[] =
{
    g_DbusSignalAttribute,
    g_DbusMethodAttribute,
    g_DbusErrorAttribute,
    nullptr
};

static void RegisterAttributes(void* eventData, void* userData)
{
    register_scoped_attributes(dbusScopedAttributes, "dbus");
}

static void GateCallback(void* eventData, void* userData)
{
    if (errorcount || sorrycount)
        return;

    std::cerr << "IPA Passes Starting for File: " << main_input_filename << std::endl;
}

int plugin_init(plugin_name_args* info, plugin_gcc_version* ver)
{
    std::cerr << "Starting Plugin: "<< info->base_name << std::endl;

    register_callback(info->base_name, PLUGIN_ATTRIBUTES, &RegisterAttributes, nullptr );
    register_callback(info->base_name, PLUGIN_ALL_IPA_PASSES_START, &GateCallback, nullptr );

    std::cerr << "Plugin Initialized, attribute registered" << std::endl;

    return 0;
}