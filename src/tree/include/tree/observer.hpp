#pragma once

#include <functional>
#include <map>

namespace treetools
{

    /**
     * A helper class to support Observer/Observable pattern.
     */
    template < typename... Args >
    class observer
    {
    public:
        using delegate_t = std::function < void (Args...) > ;
        using key_t = std::size_t;
    private:
        key_t m_sequence;
        std::map < key_t, delegate_t > m_delegates;
    public:
        observer() : m_sequence(0) {}
        observer(const observer & o) = delete;
        observer(observer && o) { *this = std::move(o); }
        observer & operator = (const observer & o) = delete;
        observer & operator = (observer && o)
        {
            m_sequence = o.m_sequence; o.m_sequence = 0;
            m_delegates = std::move(o.m_delegates);
            return *this;
        }
    public:
        /**
         * @return A reference to the list of
         *         all registered delegates
         */
        const std::map < key_t, delegate_t > & all() const
        {
            return m_delegates;
        }
    public:
        /**
         * Adds the given delegate to the list of
         * registered delegates.
         * 
         * @param d The new delegate
         * 
         * @return A unique key assigned to the
         *         given delegate
         */
        key_t subscribe(const delegate_t & d)
        {
            auto k = m_sequence++;
            m_delegates[k] = d;
            return k;
        }
        /**
         * Removes the delegate specified
         * by its unique key returned from the
         * {@see subscribe} method.
         * 
         * @param d The key of the delegate to be removed
         * 
         * @return The removed delegate, or {} if no
         *         delegate is associated with the given key
         */
        delegate_t unsubscribe(key_t k)
        {
            auto it = m_delegates.find(k);
            if (it != std::end(m_delegates))
            {
                auto d = std::move(*it);
                m_delegates.erase(it);
                return d;
            }
            return {};
        }
    public:
        /**
         * Sequentially calls all the registered delegates
         * with the given arguments.
         * 
         * @param a The arguments
         */
        void notify(Args... a) const
        {
            auto copy = m_delegates;
            for each (auto & d in copy)
            {
                d.second(a...);
            }
        }
    public:
        /**
         * Sequentially calls all the registered delegates
         * with the given arguments.
         * 
         * @param a The arguments
         */
        void operator () (Args... a) const
        {
            notify(a...);
        }
    };

} /* namespace treetools */