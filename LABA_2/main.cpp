#include <iostream>
#include "sequence.h"
#include "mutableArraySequence.h"
#include "immutableArraySequence.h"
#include "mutableListSequence.h"
#include "immutableListSequence.h"

int ReadInt()
{
    int value;

    while (true)
    {
        if (std::cin >> value)
            return value;

        std::cout << "Invalid input. Enter number: ";

        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}



int MultiplyBy2(const int& x)
{
    return x * 2;
}

bool IsEven(const int& x)
{
    return x % 2 == 0;
}

int Sum(const int& a, const int& b)
{
    return a + b;
}



void PrintSequence(Sequence<int>* seq)
{
    std::cout << "[ ";

    for (int i = 0; i < seq->get_length(); i++)
        std::cout << seq->get(i) << " ";

    std::cout << "]\n";
}



void SequenceMenu(Sequence<int>* seq)
{
    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\n===== OPERATIONS =====\n";
        std::cout << "1  Append\n";
        std::cout << "2  Prepend\n";
        std::cout << "3  InsertAt\n";
        std::cout << "4  RemoveAt\n";
        std::cout << "5  Get\n";
        std::cout << "6  GetFirst\n";
        std::cout << "7  GetLast\n";
        std::cout << "8  Length\n";
        std::cout << "9  Subsequence\n";
        std::cout << "10 Concat\n";
        std::cout << "11 Map (*2)\n";
        std::cout << "12 Where (even)\n";
        std::cout << "13 Reduce (sum)\n";
        std::cout << "14 Print\n";
        std::cout << "0  Back\n";

        std::cout << "Choose operation: ";
        choice = ReadInt();



        if (choice == 1)
        {
            std::cout << "Enter value: ";
            int value = ReadInt();

            Sequence<int>* newSeq = seq->append(value);

            if (newSeq != seq)
            {
                delete seq;
                seq = newSeq;
            }
        }



        else if (choice == 2)
        {
            std::cout << "Enter value: ";
            int value = ReadInt();

            Sequence<int>* newSeq = seq->prepend(value);

            if (newSeq != seq)
            {
                delete seq;
                seq = newSeq;
            }
        }



        else if (choice == 3)
        {
            std::cout << "Enter value: ";
            int value = ReadInt();

            std::cout << "Enter index: ";
            int index = ReadInt();

            try
            {
                Sequence<int>* newSeq = seq->insert_at(value, index);

                if (newSeq != seq)
                {
                    delete seq;
                    seq = newSeq;
                }
            }
            catch (...)
            {
                std::cout << "Invalid index\n";
            }
        }



        else if (choice == 4)
        {
            std::cout << "Enter index: ";
            int index = ReadInt();

            try
            {
                Sequence<int>* newSeq = seq->remove_at(index);

                if (newSeq != seq)
                {
                    delete seq;
                    seq = newSeq;
                }
            }
            catch (...)
            {
                std::cout << "Invalid index\n";
            }
        }



        else if (choice == 5)
        {
            std::cout << "Enter index: ";
            int index = ReadInt();

            try
            {
                std::cout << "Value: " << seq->get(index) << "\n";
            }
            catch (...)
            {
                std::cout << "Invalid index\n";
            }
        }



        else if (choice == 6)
        {
            try
            {
                std::cout << "First element: " << seq->get_first() << "\n";
            }
            catch (...)
            {
                std::cout << "Sequence is empty\n";
            }
        }



        else if (choice == 7)
        {
            try
            {
                std::cout << "Last element: " << seq->get_last() << "\n";
            }
            catch (...)
            {
                std::cout << "Sequence is empty\n";
            }
        }



        else if (choice == 8)
        {
            std::cout << "Length: " << seq->get_length() << "\n";
        }



        else if (choice == 9)
        {
            std::cout << "Enter start index: ";
            int l = ReadInt();

            std::cout << "Enter end index: ";
            int r = ReadInt();

            try
            {
                Sequence<int>* sub = seq->get_sub_sequence(l, r);

                std::cout << "Subsequence: " << *sub << "\n";

                delete sub;
            }
            catch (...)
            {
                std::cout << "Invalid indices\n";
            }
        }



        else if (choice == 10)
        {
            std::cout << "Enter number of elements to concat: ";
            int n = ReadInt();

            Sequence<int>* other = seq->create_empty_sequence();

            std::cout << "Enter elements:\n";

            for (int i = 0; i < n; i++)
            {
                int x = ReadInt();
                other->append(x);
            }

            Sequence<int>* result = seq->concat(*other);

            delete seq;
            delete other;

            seq = result;
        }



        else if (choice == 11)
        {
            std::cout << "Applying map (*2)...\n";

            Sequence<int>* result = seq->map(MultiplyBy2);

            delete seq;
            seq = result;
        }



        else if (choice == 12)
        {
            std::cout << "Filtering even numbers...\n";

            Sequence<int>* result = seq->where(IsEven);

            delete seq;
            seq = result;
        }



        else if (choice == 13)
        {
            int result = seq->reduce(Sum, 0);

            std::cout << "Reduce result: " << result << "\n";
        }



        else if (choice == 14)
        {
            std::cout << "Sequence: " << *seq << "\n";
        }
    }

    delete seq;
}



Sequence<int>* CreateArraySequence()
{
    std::cout << "\nArraySequence type:\n";
    std::cout << "1. Mutable\n";
    std::cout << "2. Immutable\n";
    std::cout << "Choice: ";

    int type = ReadInt();

    if (type == 1)
        return new MutableArraySequence<int>();
    else
        return new ImmutableArraySequence<int>();
}



Sequence<int>* CreateListSequence()
{
    std::cout << "\nListSequence type:\n";
    std::cout << "1. Mutable\n";
    std::cout << "2. Immutable\n";
    std::cout << "Choice: ";

    int type = ReadInt();

    if (type == 1)
        return new MutableListSequence<int>();
    else
        return new ImmutableListSequence<int>();
}



int main()
{
    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\n===== MAIN MENU =====\n";
        std::cout << "1. ArraySequence\n";
        std::cout << "2. ListSequence\n";
        std::cout << "0. Exit\n";

        std::cout << "Choice: ";
        choice = ReadInt();

        if (choice == 1)
        {
            Sequence<int>* seq = CreateArraySequence();
            SequenceMenu(seq);
        }

        else if (choice == 2)
        {
            Sequence<int>* seq = CreateListSequence();
            SequenceMenu(seq);
        }
    }

    return 0;
}