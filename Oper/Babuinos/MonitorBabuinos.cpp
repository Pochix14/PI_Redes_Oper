/*
Solución a los Babuinos 

Pablo Rodríguez Navarro - B66060
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <stdint.h>
#include <vector>
#include <future>

std::mutex cout_mutex; // mutex para std::cout

class MonitorBabuino {
private:
    int conteoBabuinos; /*Contador de cantidad de babuinos en el cañón*/
    int B; /*Cantidad de monos que deben haber en el cañón*/
    int N; /*Cantidad de cuerdas en el cañón*/
    std::mutex mtx; /*Mutex*/
    std::condition_variable cond; /*Variable de condición*/
    std::vector<int> cuerdas; /*Vector de cuerdas*/

public:
    MonitorBabuino(int N,int B) : /*Contructor del monitor*/
    conteoBabuinos(0),
    B(B),
    N(N), 
    cuerdas(N,0) {} /*Contructor inicializado como lista*/

    /*
    Método que simula la llegada del babuino
    */
    void llegaBabuino(const int& cuerda) {
        std::unique_lock<std::mutex> lock(mtx);

        while (conteoBabuinos >= B) {
            cond.wait(lock);
        }

        conteoBabuinos++;
        cuerdas[cuerda]++;
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout <<" El babuino llegó a la cuerda " << cuerda << ". Hay " << conteoBabuinos <<" babuinos en el cañón."<< std::endl;

        }
        cond.notify_all();
    }

   /*
    Método que simula un babuino cruzando
    */ 
   void cruzar() {
    std::unique_lock<std::mutex> lock(mtx);

    while (conteoBabuinos != B) {
        cond.wait(lock);
    }

    int mayor=cuerdas[0];
    int indice=0;
    for (int i = 0; i < cuerdas.size(); i++) {
        if (mayor < cuerdas[i]){
            mayor = cuerdas[i];
            indice = i;
        }
    }
    conteoBabuinos = conteoBabuinos-mayor;      
    cuerdas[indice]= cuerdas[indice]-mayor; // 0
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Cruzando "<< mayor <<" babuinos por la cuerda "<< indice << ". Hay "<< conteoBabuinos <<" babuinos en el cañon: " << std::endl;

    }
    cond.notify_all();
    }
};


int main() {
    int total = 50; /*Indica la cantidad de Babuinos (hilos) que se crearán*/
    int B = 8; /*Indica la cantidad de babuinos que deben haber en el cañón*/
    int N= 5; /*Indica la cantidad de cuerdas que hay en el cañón*/

    MonitorBabuino babuino(N, B); /*Instancia de Monitor*/

    /*Utilización de un pool para los hilos*/
    std::vector<std::future<void>> futures;

   for (int i = 0; i < total; ++i) {
        int cuerda = rand() % N;
        futures.emplace_back(std::async(std::launch::async, [&babuino, cuerda]() {
            babuino.llegaBabuino(cuerda);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            babuino.cruzar();
        }));
    }

    for (auto& future : futures) {/*Esperar a que todas las tareas se completen*/
        future.get();
    }
    return 0;
}
