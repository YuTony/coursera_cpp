#include <iostream>
#include <map>
#include <string>
using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

TaskStatus next(TaskStatus ts) {
    return static_cast<TaskStatus>(static_cast<int>(ts) + 1);
}

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
   public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return data.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person) {
        data[person][TaskStatus::NEW]++;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
        TasksInfo mod, no_mod;
        for (TaskStatus i = TaskStatus::NEW; i != TaskStatus::DONE; i = next(i)) {
            mod[next(i)] = min(task_count, data[person][i]);
            task_count -= mod[next(i)];
        }

        for (TaskStatus i = TaskStatus::NEW; i != TaskStatus::DONE; i = next(i)) {
            no_mod[i] = data[person][i] - mod[next(i)];
            data[person][i] += mod[i] - mod[next(i)];
        }

        data[person][TaskStatus::DONE] += mod[TaskStatus::DONE];

        for (int i = 0; i < 4; i++) {
            TaskStatus c = static_cast<TaskStatus>(i);
            if (mod[c] == 0) {
                mod.erase(c);
            }
        }

        for (int i = 0; i < 4; i++) {
            TaskStatus c = static_cast<TaskStatus>(i);
            if (no_mod[c] == 0) {
                no_mod.erase(c);
            }
        }

        return tie(mod, no_mod);
    }

   private:
    map<string, TasksInfo> data;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
/*void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks"
         << ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"
         << ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested"
         << ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}*/