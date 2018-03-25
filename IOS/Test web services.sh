# Test web services

# Create Users [DONE]
	curl -H "Content-Type: application/json" -XPOST -d '{"login" : "test", "password" : "test"}' "localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.users/create" | less

# Check correct login [DONE]
	curl -H "Content-Type: application/json" -XGET "localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.users/login/username/test/password/test"

# Check incorrect login [DONE]
	curl -H "Content-Type: application/json" -XGET "localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.users/login/username/test/password/test1"

# Create person [DONE]
	curl -H "Content-Type: application/json" -XPOST -d '{"name" : "test", "familyName" : "test"}' "localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.person/create/user/1" | less

# Create settings [DONE]
	curl -H "Content-Type: application/json" -XPOST -d '{"breakTime" : 5, "pomodoroTime" : 25, "pomodoroGoal" : 10, "taskGoal" : 10}' "localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.settings/create/user/1" | less

# Create pomodoro [DONE]
	curl -H "Content-Type: application/json" -XPOST -d '{"pdate" : "2017-12-02T18:31:42"}' "localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.pomodoro/create/user/1" | less

# Create team [DONE]
	curl -H "Content-Type: application/json" -XPOST -d '{"name": "test"}' "localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.team/create/user/1" | less

# List members [DONE]
	curl -H "Content-Type: application/json" -XGET "localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.team/team/1/members" | less

# Create list [DONE]
	curl -H "Content-Type: application/json" -XPOST -d '{"title" : "test"}' "localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.list/create/team/1" | less

# Create task [DONE]
	curl -H "Content-Type: application/json" -XPOST -d '{"name" : "test", "info" : "info test"}' "localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.task/create/list/1" | less

# Add finish date [DONE]
	curl -H "Content-Type: application/json" -XPUT -d '{"name" : "test", "dateFinish" : "2017-12-02T18:31:42"}' "localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.task/edit/1" | less

