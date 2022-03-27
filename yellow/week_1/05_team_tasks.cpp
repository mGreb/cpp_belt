#include <map>
#include <tuple>
#include <string>
#include <iostream>
#include <vector>

// comment out before sending!
// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// comment out before sending!
// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
typedef std::map<TaskStatus, int> TasksInfo;

class TeamTasks {
	std::map<std::string, TasksInfo> data;
	static TaskStatus Elevate(const TaskStatus &t) {
		if (t == TaskStatus::NEW)         return TaskStatus::IN_PROGRESS;
		if (t == TaskStatus::IN_PROGRESS) return TaskStatus::TESTING;
		return TaskStatus::DONE;
	}
	
public:
	// Получить статистику по статусам задач конкретного разработчика
	[[nodiscard]] const TasksInfo& GetPersonTasksInfo(const std::string& person) const {
		return data.at(person);
	}
	
	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const std::string& person) {
		data[person][TaskStatus::NEW] += 1;
	}
	
	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(const std::string& person, int task_count) {
		// if no such person - return empty tuple
		if (data.count(person) == 0)
			return {{}, {}};
		
		// determine correct task count
		auto &p = data[person];
		int total_persons_tasks = 0;
		for (const auto &[key, value] : p)
			total_persons_tasks += value;
		if (p.count(TaskStatus::DONE) != 0)
			task_count = std::min(task_count, total_persons_tasks - p.at(TaskStatus::DONE));
		else
			task_count = std::min(task_count, total_persons_tasks);
		
		// unfold all tasks into vector for easy elevation
		std::vector<TaskStatus> tasks_old(total_persons_tasks);
		int counter = 0;
		for (const auto &[key, value] : p)
			for (int i = 0; i < value && counter <= total_persons_tasks; ++i, ++counter)
				tasks_old[counter] = key;
		
		// copy unfolded vector of tasks and elevate
		std::vector<TaskStatus> tasks_new = tasks_old;
		for (int i = 0; i < task_count; ++i)
			tasks_new[i] = Elevate(tasks_old[i]);
		
		// fold vector back to calculate new state of TaskInfo
		TasksInfo p_new;
		for (const auto &elem : tasks_new)
			++p_new[elem];
		p = p_new;
		
		// fill updated and untouched by comparing tasks vectors
		TasksInfo updated, untouched;
		for (size_t i = 0; i < tasks_new.size(); ++i)
			if (tasks_old[i] != tasks_new[i])
				++updated[tasks_new[i]];
			else
				if (tasks_new[i] != TaskStatus::DONE)
					++untouched[tasks_new[i]];
		
		return {updated, untouched};
	}
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
	std::cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
	     ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
	     ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
	     ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << std::endl;
}

int main() {
	TeamTasks tasks;
	tasks.AddNewTask("Ilia");
	for (int i = 0; i < 3; ++i) {
		tasks.AddNewTask("Ivan");
	}
	std::cout << "Ilia's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
	std::cout << "Ivan's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
	
	TasksInfo updated_tasks, untouched_tasks;
	
	tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Ivan", 2);
	std::cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	std::cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);
	
	tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Ivan", 2);
	std::cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	std::cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);
	
	return 0;
}
