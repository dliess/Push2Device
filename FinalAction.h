#ifndef FINAL_ACTION_H
#define FINAL_ACTION_H

#include <utility> //std::move

template <class F>
class FinalAction
{
public:
    explicit FinalAction(F f) noexcept : m_function(std::move(f)) {}
    FinalAction(FinalAction&& other) noexcept : m_function(std::move(other.m_function)), m_active(other.m_active)
    {
        other.m_active = false;
    }
    FinalAction(const FinalAction&) = delete;
    FinalAction& operator=(const FinalAction&) = delete;
    FinalAction& operator=(FinalAction&&) = delete;
    void disable()
    {
        m_active = false;
    }
    ~FinalAction() noexcept
    {
        if (m_active) m_function();
    }

private:
    F m_function;
    bool m_active{true};
};

template<class F>
FinalAction<F> finally(F&& f) noexcept
{
    return FinalAction<F>(std::forward<F>(f));
}

#endif // FINAL_ACTION_H
