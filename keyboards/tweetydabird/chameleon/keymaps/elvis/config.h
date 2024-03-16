// Copyright 2023 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define WS2812_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the WS2812 implementation uses the PIO0 peripheral

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 175

// Prevent normal rollover on alphas from accidentally triggering mods.
// "IGNORE_MOD_TAP_INTERRUPT is no longer necessary as it is now the default behavior of mod-tap keys
// #define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

// #define WPM_ALLOW_COUNT_REGRESSION
