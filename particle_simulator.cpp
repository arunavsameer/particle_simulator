#include <bits/stdc++.h>
using namespace std;

#define dt 0.0001
#define gravity make_pair(0.0, -10.0)
#define boundary make_pair(10.0, 10000000.0)
#define CoE 0.5
float time_ = 0;

float min(float a, float b){
    return (a > b) ? b : a;
}

int collisions = 0;

class particle{
protected:
    float mass = 1;
    float radius = 0.1;
    pair<float, float> acceleration;
    pair<float, float> velocity;
    pair<float, float> position;
    pair<float, float> prev_position;

    float distance(particle B){
        float dist = (position.first - B.position.first)*(position.first - B.position.first) + (position.second - B.position.second)*(position.second - B.position.second);
        return sqrt(dist);
    }

    void move(){
        acceleration = gravity;

        prev_position = position;

        velocity.first += acceleration.first*dt;
        velocity.second += acceleration.second*dt;

        position.first += velocity.first*dt;
        position.second += velocity.second*dt;
        collide_boundary();
    }
    void collide_boundary(){
        if(position.first < radius || position.first > boundary.first - radius){
            collisions++;
            float gap = abs(min(radius - prev_position.first ,  boundary.first - radius - prev_position.first));
            float delta = ((abs(velocity.first) * dt) - gap) * CoE;
            if(position.first < radius){
                position.first = radius + delta;
            }else{
                position.first = (boundary.first - radius - delta);
            }
            velocity.first = -1 * CoE * velocity.first; 
        }
        if(position.second < radius || position.second > boundary.second - radius){
            collisions++;
            float gap = abs(min(radius - prev_position.second,  boundary.second - radius - prev_position.second));
            float delta = ((abs(velocity.second) * dt) - gap) * CoE;
            if(position.second < radius){
                position.second = radius + delta;
            }else{
                position.second = (boundary.second - radius - delta);
            }
            velocity.second = -1 * CoE * velocity.second; 
        }
    }
    void collide_particle(particle &B){
        //cout << "collided" <<endl;
        collisions++;
        pair<float, float> prev_velocity = velocity;
        pair<float, float> velocity_cm = make_pair(((mass*velocity.first + B.mass*B.velocity.first)/(mass + B.mass)), ((mass*velocity.second + B.mass*B.velocity.second)/(mass + B.mass)));
        velocity.first = velocity_cm.first - (((B.mass*CoE)/(mass + B.mass))*(velocity.first - B.velocity.first));
        velocity.second = velocity_cm.second - (((B.mass*CoE)/(mass + B.mass))*(velocity.second - B.velocity.second));

        B.velocity.first = velocity_cm.first + (((mass*CoE)/(mass + B.mass))*(prev_velocity.first - B.velocity.first));
        B.velocity.second = velocity_cm.second + (((mass*CoE)/(mass + B.mass))*(prev_velocity.second - B.velocity.second));
    }
    particle(pair<float, float> p){
        position = p;
    }
    particle(pair<float, float> p, pair<float, float> v){
        position = p;
        velocity = v;
    }
    particle(){
        velocity = make_pair(0.0,  0.0);
        position = make_pair(5.0, 5.0);
    }

    friend class simulation;
};

class simulation{
    vector<particle> particles;
public:

    void generate_case(){
        particle A(make_pair(5, 5));
        A.mass = 1000;
        A.velocity = make_pair(0, -1);
        particle B(make_pair(5, 2));
        B.mass = 1;
        B.velocity = make_pair(0, 0); 
        particles.clear();
        particles.push_back(A);
        particles.push_back(B);
    }

    void generate_particles(int n){
        for(int i = 0; i < n; i++){
            particle A(make_pair(5, i+4));
            particles.push_back(A);
        }
    }
    void simulate(){
        vector<particle>::iterator it = particles.begin();
        vector<particle>::iterator it_ = particles.begin();
        while(it != particles.end()){
            it -> move();
            it++;
        }
        it = particles.begin();
        while(it != particles.end()){
            it_++;
            while(it_ != particles.end()){
                if(it -> distance(*it_) <= 2*it->radius){
                    it -> collide_particle(*it_);   
                }
                it_++;
            }
            it++;
            it_ = it;
        }
        time_ += dt;
    }
    void print_position(){
        cout << collisions <<" ";
        cout << time_ <<" ";
        for(auto p: particles){
            cout << p.position.first <<" "<<p.position.second <<" ";
        }
        cout << endl;
    }
    void play(){
        while(1){
            simulate();
            print_position();
        }
    }
};

int main(){
    simulation A;
    A.generate_particles(2);
    A.play();
}