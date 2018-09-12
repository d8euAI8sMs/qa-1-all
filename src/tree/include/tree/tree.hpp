#pragma once

#include <vector>
#include <memory>

#include <tree/observer.hpp>

namespace treetools
{
    
    class unmovable_tree_error : public std::logic_error
    {
        unmovable_tree_error(const std::string & message)
            : std::logic_error(message) {}
    };

    /**
     * The class implements an observable tree data structure.
     */
    template < typename T >
    class tree
    {
    public:
        using data_t = T;
    public:
        enum _event_type : int
        {
            hierarchy_change, child_add, child_remove, data_change
        };
        struct event
        {
            tree * source;
            int    event_type;
            tree * arg;
        };
    public:
        using observer_t = observer < const event & > ;
    private:
        tree * m_parent;
        data_t m_data;
        std::vector < std::unique_ptr < tree > > m_children;
    public:
        observer_t m_observer;
    public:
        /**
         * Constructs the new tree and initializes
         * the data forwarding the given arguments
         * to its constructor.
         * 
         * @param a The arguments
         */
        template < typename... Args >
        tree(Args&&... a)
            : m_data(std::forward < Args > (a) ...)
            , m_parent(nullptr)
        {
        }
    public:
        tree(const tree &) = delete;
        tree(tree && o) { *this = std::move(o); }
    public:
        tree & operator = (const tree &) = delete;
        /**
         * Moves the given object into this tree.
         * 
         * <p/>
         * Beware of moving tree that is a child of
         * another tree. Such operation is not permitted
         * since it cannot be implemented transparent
         * and would have a lot of undesirable side effects.
         * 
         * @param o The object to be moved
         * 
         * @throws unmovable_tree_error If this or `o` has
         *                              non-null parent
         */
        tree & operator = (tree && o)
        {
            if (m_parent || o.m_parent)
                throw unmovable_tree_error(
                    "move operation is only permitted for parentless trees");
            m_children = std::move(o.m_children);
            m_observer = std::move(o.m_observer);
            m_data = std::move(o.m_data);
            return *this;
        }
    public:
        /**
         * Adds the new child to the tree and returns a
         * pointer to it. The lifecycle of the returned
         * value is maintained by this instance
         * and should not be deleted manually.
         * 
         * <p/>
         * Generates `child_add` notification with the
         * newly created child as an argument.
         * 
         * <p/>
         * When the child is added to or removed from the
         * tree, it also generates the `hierarchy_change`
         * event with the old parent as an argument.
         * 
         * @return The newly created child
         */
        tree * add()
        {
            tree e; e._parent(this);
            m_children.emplace_back(new tree(std::move(e)));
            m_observer({ this, child_add, m_children.back().get() });
            return m_children.back().get();
        }
        /**
         * Removes the specified child from the tree.
         * 
         * <p/>
         * Generates `child_remove` notification with the
         * removed child as an argument.
         * 
         * <p/>
         * When the child is added to or removed from the
         * tree, it also generates the `hierarchy_change`
         * event with the old parent as an argument.
         * 
         * @return The removed child
         */
        std::unique_ptr < tree > remove(const tree * e)
        {
            std::unique_ptr < tree > r;
            for (auto it = std::begin(m_children);
                 it != std::end(m_children);
                 ++it)
            {
                if (it->get() == e)
                {
                    r = std::move(*it);
                    m_children.erase(it);
                    r->_parent(nullptr);
                    m_observer({ this, child_remove, r.get() });
                    break;
                }
            }
            return r;
        }
    public:
        tree * parent() { return m_parent; }
        const tree * parent() const { return m_parent; }
        std::vector < std::unique_ptr < tree > > & children() { return m_children; }
        const std::vector < std::unique_ptr < tree > > & children() const { return m_children; }
        const data_t & data() const { return m_data; }
        data_t & data() { return m_data; }
        /**
         * Sets the data associated with this instance.
         * 
         * <p/>
         * Generates `data_change` notification. The type
         * of the associated data must provide the `==`
         * operator in order to generate notification only
         * in case if the data is really changed.
         * 
         * @param d The new data
         */
        tree & data(const data_t & d) { _data(d); return *this; }
        tree & data(data_t && d) { _data(std::move(d)); return *this; }
    private:
        void _parent(tree * p)
        {
            if (m_parent == p) return;
            tree * _old = m_parent;
            this->m_parent = p;
            m_observer({ this, hierarchy_change, _old });
        }
        void _data(const data_t & data)
        {
            if (m_data == data) return;
            m_data = data;
            m_observer({ this, data_change, nullptr });
        }
        void _data(data_t && data)
        {
            if (m_data == data) return;
            m_data = std::move(data);
            m_observer({ this, data_change, nullptr });
        }
    };

} /* namespace treetools */