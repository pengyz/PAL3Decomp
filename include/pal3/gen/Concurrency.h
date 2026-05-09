#pragma once
// Auto-generated from IDA decomp - Concurrency
// 4 methods

class Concurrency {
public:
    unsigned int details::VirtualProcessor::GetExecutionResourceId();  // 0x004790F0
    static struct Concurrency::IThreadProxy *__thiscall(Concurrency::details::InternalContextBase *this) details::InternalContextBase::GetProxy();  // 0x00479250
    bool details::VirtualProcessor::IsThrottled();  // 0x004B4830
    void details::ExternalStatistics::MarkInactive();  // 0x00532D50
};
