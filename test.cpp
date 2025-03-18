#include "Dict.h"
#include <iostream>
#include <cassert>

int main()
{
    // ایجاد یک دیکشنری
    Dict dict;

    // تست عملیات درج
    std::cout << "Inserting key-value pairs...\n";
    dict.insert(1, 100);
    dict.insert(2, 200);
    dict.insert(3, 300);
    dict.insert(4, 400);
    dict.insert(5, 500);

    // چاپ دیکشنری
    std::cout << "Dictionary after insertions: " << dict << "\n";

    // تست عملیات جستجو
    std::cout << "Testing find operation...\n";
    assert(dict.find(1) == 100);
    assert(dict.find(3) == 300);
    assert(dict.find(5) == 500);
    std::cout << "Find operation passed.\n";

    // تست برخوردها (collisions)
    std::cout << "Testing collision handling...\n";
    dict.insert(9, 900);  // ممکن است تصادم رخ دهد
    dict.insert(17, 1700); // احتمال برخورد بیشتر
    assert(dict.find(9) == 900);
    assert(dict.find(17) == 1700);
    std::cout << "Collision handling passed.\n";

    // تست عملیات حذف
    std::cout << "Testing erase operation...\n";
    dict.erase(3);
    try
    {
        dict.find(3); // باید استثنا بدهد
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Key 3 successfully deleted.\n";
    }

    dict.erase(9);
    try
    {
        dict.find(9); // باید استثنا بدهد
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Key 9 successfully deleted.\n";
    }

    // چاپ دیکشنری بعد از حذف
    std::cout << "Dictionary after deletions: " << dict << "\n";

    // تست رشد دیکشنری (resize)
    std::cout << "Testing resize operation...\n";
    dict.insert(6, 600);
    dict.insert(7, 700);
    dict.insert(8, 800);
    dict.insert(10, 1000); // اینجا ظرفیت افزایش پیدا می‌کند
    dict.insert(11, 1100);

    // چاپ دیکشنری بعد از افزایش ظرفیت
    std::cout << "Dictionary after resizing: " << dict << "\n";

    // تست مجدد جستجو
    std::cout << "Testing find after resizing...\n";
    assert(dict.find(1) == 100);
    assert(dict.find(5) == 500);
    assert(dict.find(11) == 1100);
    std::cout << "Find after resizing passed.\n";

    // تست حذف کلیدهای ناموجود
    std::cout << "Testing erase for non-existing keys...\n";
    try
    {
        dict.erase(20); // کلید ناموجود
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Exception caught for non-existing key: " << e.what() << "\n";
    }

    std::cout << "All tests passed successfully.\n";
    return 0;
}