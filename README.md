# maven-deps

## Общее описание


## Описание всех функций и настроек


## Зависимости 

- [Java](https://www.oracle.com/java/technologies/downloads/)
- [PlantUML](https://github.com/plantuml/plantuml/releases/download/v1.2024.8/plantuml.jar)

## Cборка проекта

Необходимые зависимости для разработки:
- gcc || clang || msvc
- [Conan](https://conan.io/downloads)
- [CMake](https://cmake.org/download/)

Пример профиля gcc (под linux):
```yml
[settings]
arch=x86_64
build_type=Release
compiler=gcc
compiler.cppstd=gnu17
compiler.libcxx=libstdc++11
compiler.version=13
os=Linux
```

Далее в терминале для сборки:
```bash
conan profile detect --force
mkdir build
conan install . --output-folder=build --build=missing
cd build
cmake .. --preset conan-release 
# или cmake .. --preset conan-default 
cmake --build . --config Release
```

## Примеры использования
```bash
./maven_deps -p org.json:json:20230227 -v ../for_test/plantuml.jar

```

## Результаты тестов
Запуск тестов происходит в директории build после сборки проекта командой:
```bash
ctest
```
![img](screenshots/test.png)