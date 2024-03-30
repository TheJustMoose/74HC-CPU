#pragma once

#include <memory>

class Word;

std::shared_ptr<Word> And();
std::shared_ptr<Word> Or();
std::shared_ptr<Word> Eq();
std::shared_ptr<Word> Ne();
std::shared_ptr<Word> Le();
std::shared_ptr<Word> Ge();
std::shared_ptr<Word> Minus();
std::shared_ptr<Word> Temp();
