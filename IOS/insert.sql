select * from users;
select * from settings;
select * from pomodoro;
select * from person;
select * from team;
select * from list;
select * from task;

insert into list values (2, 'list1', 10);
insert into task values (1, 'task1', null, null, 3);
insert into task values (2, 'task2', null, null, 3);
insert into task values (3, 'task3', null, null, 2);
insert into task values (4, 'task4', null, null, 2);

insert into users values (1, 'account1', 'account1');
insert into users values (2, 'account2', 'account2');
insert into users values (3, 'account3', 'account3');
insert into users values (4, 'account4', 'account4');
insert into users values (5, 'account5', 'account5');
insert into users values (6, 'account6', 'account6');
insert into users values (7, 'account7', 'account7');
insert into users values (8, 'account8', 'account8');
insert into users values (9, 'account9', 'account9');
insert into users values (10, 'account10', 'account10');

insert into team values (1, 'Team1');
insert into team values (2, 'Team2');
insert into team values (3, 'Team3');

insert into person values ('Name1', 'FamilyName1', null, 1, 1);
insert into person values ('Name2', 'FamilyName2', null, 1, 2);
insert into person values ('Name3', 'FamilyName3', null, 1, 3);
insert into person values ('Name4', 'FamilyName4', null, 2, 4);
insert into person values ('Name5', 'FamilyName5', null, 2, 5);
insert into person values ('Name6', 'FamilyName6', null, 2, 6);
insert into person values ('Name7', 'FamilyName7', null, 3, 7);
insert into person values ('Name8', 'FamilyName8', null, 3, 8);
insert into person values ('Name9', 'FamilyName9', null, 3, 9);
insert into person values ('Name10', 'FamilyName10', null, 3, 10);

insert into SETTINGS values (5, 30, 10, 20, 1);
insert into SETTINGS values (5, 30, 10, 20, 2);
insert into SETTINGS values (5, 30, 10, 20, 3);
insert into SETTINGS values (5, 30, 10, 20, 4);
insert into SETTINGS values (5, 30, 10, 20, 5);
insert into SETTINGS values (5, 30, 10, 20, 6);
insert into SETTINGS values (5, 30, 10, 20, 7);
insert into SETTINGS values (5, 30, 10, 20, 8);
insert into SETTINGS values (5, 30, 10, 20, 9);
insert into SETTINGS values (5, 30, 10, 20, 10);

insert into list values (1, 'List1Team1', 1);
insert into list values (2, 'List2Team1', 1);
insert into list values (3, 'List1Team2', 2);
insert into list values (4, 'List2Team2', 2);
insert into list values (5, 'List1Team3', 3);
insert into list values (6, 'List2Team3', 3);

insert into task values (1, 'Task1List1Team1', 'Info about Task1 from List1 of Team1', null, 1);
insert into task values (2, 'Task2List1Team1', 'Info about Task2 from List1 of Team1', null, 1);
insert into task values (3, 'Task1List2Team1', 'Info about Task1 from List2 of Team1', null, 2);
insert into task values (4, 'Task2List2Team1', 'Info about Task2 from List2 of Team1', null, 2);
insert into task values (5, 'Task1List1Team2', 'Info about Task1 from List1 of Team2', null, 3);
insert into task values (6, 'Task2List1Team2', 'Info about Task2 from List1 of Team2', null, 3);
insert into task values (7, 'Task1List2Team2', 'Info about Task1 from List2 of Team2', null, 4);
insert into task values (8, 'Task2List2Team2', 'Info about Task2 from List2 of Team2', null, 4);
insert into task values (9, 'Task1List1Team3', 'Info about Task1 from List1 of Team3', null, 5);
insert into task values (10, 'Task2List1Team3', 'Info about Task2 from List1 of Team3', null, 5);
insert into task values (11, 'Task1List2Team3', 'Info about Task1 from List2 of Team3', null, 6);
insert into task values (12, 'Task2List2Team3', 'Info about Task2 from List2 of Team3', null, 6);