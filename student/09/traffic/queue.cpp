#include "queue.hh"

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle):
    first_(nullptr),
    last_(nullptr),
    is_green_(false),
    cycle_(cycle),
    size_(0),
    cycle_state_(0),
    light_status_("RED")
{

}

Queue::~Queue()
{
    Vehicle* current = last_;
    while (current != nullptr)
    {
        Vehicle* tmp = current->next;
        delete current;
        current = tmp;
    }
}

void Queue::enqueue(string reg)
{
    if (!is_green_)
    {
        Vehicle* new_car = new Vehicle;
        new_car->reg_num = reg;
        new_car->next = last_;
        new_car->prev = nullptr;

        if (size_ > 0)
        {
            last_->prev = new_car;
        }

        last_ = new_car;

        ++size_;

        if (size_ == 1)
        {
            first_ = last_;
        }

    }
    else
    {
        std::cout << light_status_ << ": The vehicle " << reg << "  need not stop to wait" << std::endl;
    }

}

void Queue::switch_light()
{

    if (is_green_)
    {
        light_status_ = "RED";
        is_green_ = false;
        if (size_ == 0)
        {
            std::cout <<light_status_ << ": No vehicles waiting in traffic lights" << std::endl;
            return;
        }
    }
    else
    {
        light_status_ = "GREEN";
        is_green_ = true;
        if (size_ == 0)
        {
            std::cout <<light_status_ << ": No vehicles waiting in traffic lights" << std::endl;
            return;
        }


        std::cout << light_status_ << ": Vehicle(s)";

        cycle_state_ = cycle_;
        while (size_ != 0 and cycle_state_ != 0)
        {

            dequeue();
            --cycle_state_;
        }
        std::cout << " can go on" << std::endl;
    }
    light_status_ = "RED";
    is_green_ = false;
}




void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;

}

void Queue::print()
{
    if (is_green_)
    {
        light_status_ = "GREEN";
    }
    else
    {
        light_status_ = "RED";
    }

    if (size_ == 0)
    {
        std::cout << light_status_ << ": No vehicles waiting in traffic lights" << std::endl;
    }
    else
    {
        std::cout << light_status_ << ": Vehicle(s)";
        Vehicle* current = first_;

        while (current != nullptr)
        {
            std::cout << " " <<current->reg_num;
            current = current->prev;
        }
        std::cout << " waiting in traffic lights" << std::endl;
    }
}

void Queue::dequeue()
{
    if (first_ == nullptr)
    {
        return;
    }

    Vehicle* old_first = first_;
    std::cout << " " << old_first->reg_num;
    Vehicle* new_first = old_first->prev;

    if (first_ == last_)
    {
        last_ = nullptr;
        delete old_first;
        first_ = new_first;
    }
    else
    {
        delete old_first;
        first_ = new_first;
    }

    --size_;
    return;

}
