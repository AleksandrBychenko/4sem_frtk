#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


//создаем вектор из структур
struct Statistics
{

    int cout;
    std::string  word;
};


std::string prepare (const std::string& s)
{
    //должен убрать знак с конца слова и перевести в нижный регистор 
    //

    std::string result(s);
    std::transform(s.begin(), s.end(), result.begin(), ::tolower);// функция для перевода в нижний регистр 
    
   
    if (result.back() == ',' || result.back() == '.' || result.back() == '!' || result.back() == '?'  ) {
        result.pop_back(); // функция для удаления знака препинания сразу же после слова 
    }
    
    return result;


}

bool how_sort(Statistics s1, Statistics s2) {// функция для того как сортивать 
    return s1.cout > s2.cout;
}



int main()
{

    std::vector<Statistics> otvet;
    std::map <std::string, int>  how_many;
    //std::string s("SasHa,"); проверка 
   // std::cout << prepare(s) << std::endl  ;



    std::fstream file("file1.txt");
    if (file.is_open()) {
        std::string word;
        while (!file.eof())
        {
            file >> word; //передаем файл в строку 
            word = prepare(word); 
           // how_many.insert(make_pair(word, +1 )); просто создает меп 
            how_many[word] = how_many[word] + 1;// создает и если уже создано то добавляет значение 

        }


     // вывод map ;
       Statistics a;
       std::map<std::string, int>::iterator it;
       for (it = how_many.begin(); it != how_many.end(); ++it) 
       {
           a.cout = it->second;
           a.word = it->first;
           otvet.push_back(a);

          //std::cout << it->first << " => " << it->second << '\n';
          //данная функция может выводить map : при рабате с векторами стракт мы передаем через  посредника а не сразу же 
       }

       std::sort(otvet.begin(), otvet.end(),how_sort);//функция сортировки 

       for (int i = 0; i < otvet.size(); i++) {//вывод ответа 
           std::cout << otvet[i].word << "!!! =>" << otvet[i].cout << '\n';
       }


     
       file.close();
    }
    else
    {
        std::cout << "File is not open " ;
    }
    return 0;
}

