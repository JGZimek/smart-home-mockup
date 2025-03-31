#include "gate.hpp"

// pins for the servo driver L9110
#define IA1 18
#define IB2 19

// bins for the buttons simulating triggers for the gate opening and closing
int buttonGate = 4; 
bool isClosed = true; // flag indicating if the gate is closed, default assumed true

#define GATE_TAG "app_gate"
bool init_gate(){
    pinMode(IA1, OUTPUT);
    pinMode(IB2, OUTPUT);
    digitalWrite(IA1, LOW); // Servo initially off
    digitalWrite(IB2, LOW);
    pinMode(buttonGate, INPUT_PULLUP);
    ESP_LOGI(GATE_TAG, "Gate motor controls are initialized on pins %d and %d", IA1, IB2);
    return true;
}

void open_gate(){
    Serial.println("Gate is opening");
    digitalWrite(IB2, HIGH);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    digitalWrite(IB2, LOW);
    Serial.println("Gate is opened");
    isClosed = false;
}

void close_gate(){
    Serial.println("Gate is closing");
    digitalWrite(IA1, HIGH);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    digitalWrite(IA1, LOW);
    Serial.println("Gate is closed");
    isClosed = true;
}



void handle_gate(){ 

    if(digitalRead(buttonGate) == LOW && isClosed && mock_lock_open()){
        open_gate();
    }
    else if(digitalRead(buttonGate) == LOW && !isClosed && mock_lock_open()){
        close_gate();
    }
}