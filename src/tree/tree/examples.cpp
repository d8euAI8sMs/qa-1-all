#include <string>
#include <iostream>

#include <tree/tree.hpp>

using namespace treetools;
using mytree_t = tree < std::string > ;

void main()
{
    auto h = [] (const mytree_t::event & e) {
        std::cout << "event from [" << e.source->data() << "]: ";

        switch (e.event_type)
        {
        case mytree_t::hierarchy_change:
            std::cout << "hierarchy_change ";
            std::cout << "(new parent is [" << (e.source->parent() ? e.source->parent()->data() : "nullptr") << "], ";
            std::cout << "old parent is [" << (e.arg ? e.arg->data() : "nullptr") << "])";
            break;
        case mytree_t::child_add:
            std::cout << "child_add ";
            std::cout << "(new child is [" << e.arg->data() << "])";
            break;
        case mytree_t::child_remove:
            std::cout << "child_remove ";
            std::cout << "(old child is [" << e.arg->data() << "])";
            break;
        case mytree_t::data_change:
            std::cout << "data_change ";
            std::cout << "(new data is [" << e.source->data() << "])";
            break;
        default:
            std::cout << "unknown "; break;
        }

        std::cout << std::endl;
    };

    mytree_t t;
    auto key = t.m_observer.subscribe(h);

    t.data("new title"); // notifies `h` with `data_change`
    
    auto t2 = t.add(); // notifies `h` with `child_add`
    t2->data("new title 2");
    auto key2 = t2->m_observer.subscribe(h);

    t.remove(t2); // notifies `h` with `child_remove`
                  //     from `t`
                  // and with `hierarchy_change`
                  //     from `t2` (arrives prior to
                  //                notification from `t`)

    system("pause");
}