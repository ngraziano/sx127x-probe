/*
 * SX127x Probe - STM32F1x software to monitor LoRa timings
 * 
 * Copyright (c) 2019 Manuel Bleichenbacher
 * Licensed under MIT License
 * https://opensource.org/licenses/MIT
 * 
 * LoRa timing analyzer
 */

#ifndef _TIMING_ANALYZER_H_
#define _TIMING_ANALYZER_H_

#include <stdint.h>

enum LoraTxRxPhase
{
    LoraPhaseIdle,
    LoraPhaseTransmitting,
    LoraPhaseBeforeRx1Window,
    LoraPhaseInRx1Window,
    LoraPhaseBeforeRx2Window,
    LoraPhaseInRx2Window
};

enum LoraTxRxResult
{
    LoraResultNoDownlink,
    LoraResultDownlinkInRx1,
    LoraResultDownlinkInRx2
};


class TimingAnalyzer
{
public:
    TimingAnalyzer();

    void OnTxStart(uint32_t time);
    void OnRxStart(uint32_t time);
    void OnDoneInterrupt(uint32_t time);
    void OnTimeoutInterrupt(uint32_t time);

    void SetRxSymbolTimeout(uint16_t numTimeoutSymbols) { this->numTimeoutSymbols = numTimeoutSymbols; }
    void SetBandwidth(uint32_t bandwidth) { this->bandwidth = bandwidth; }
    void SetCodingRate(uint8_t codingRate) { this->codingRate = codingRate; }
    void SetImplicitHeader(uint8_t implicitHeader) { this->implicitHeader = implicitHeader; }
    void SetSpreadingFactor(uint8_t spreadingFactor) { this->spreadingFactor = spreadingFactor; }
    void SetCrcOn(uint8_t crcOn) { this->crcOn = crcOn; }
    void SetPreambleLength(uint16_t preambleLength) { this->preambleLength = preambleLength; }
    void SetPayloadLength(uint8_t payloadLength) { this->payloadLength = payloadLength; }
    void SetLowDataRateOptimization(uint8_t lowDataRateOptimization) { this->lowDataRateOptimization = lowDataRateOptimization; }

private:
    void ResetPhase();
    void OnRxTxCompleted();
    void PrintTimestamp(uint32_t timestamp);
    uint32_t CalculateAirTime();

    LoraTxRxPhase phase;
    LoraTxRxResult result;
    uint32_t txStartTime;
    uint32_t txEndTime;
    uint32_t rx1Start;
    uint32_t rx1End;
    uint32_t rx2Start;
    uint32_t rx2End;

    uint32_t bandwidth;
    uint16_t numTimeoutSymbols;
    uint8_t codingRate;
    uint8_t implicitHeader;
    uint8_t spreadingFactor;
    uint8_t crcOn;
    uint16_t preambleLength;
    uint8_t payloadLength;
    uint8_t lowDataRateOptimization;
};

#endif
