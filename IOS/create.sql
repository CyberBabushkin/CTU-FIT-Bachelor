CREATE TABLE list (
    list_id        INTEGER NOT NULL,
    title          VARCHAR(50) NOT NULL,
    team_team_id   INTEGER NOT NULL
);

ALTER TABLE list ADD CONSTRAINT list_pk PRIMARY KEY ( list_id );

CREATE TABLE person (
    name            VARCHAR(50) NOT NULL,
    family_name     VARCHAR(50) NOT NULL,
    avatar          LONG VARCHAR,
    team_team_id    INTEGER,
    users_user_id   INTEGER NOT NULL
);

ALTER TABLE person ADD CONSTRAINT person_pk PRIMARY KEY ( users_user_id );

CREATE TABLE pomodoro (
    pomodoro_id      INTEGER NOT NULL,
    "date"           DATE NOT NULL,
    person_user_id   INTEGER NOT NULL
);

ALTER TABLE pomodoro ADD CONSTRAINT pomodoro_pk PRIMARY KEY ( pomodoro_id );

CREATE TABLE settings (
    break_time             INTEGER NOT NULL,
    pomodoro_time          INTEGER NOT NULL,
    pomodoro_goal          INTEGER NOT NULL,
    task_goal              INTEGER NOT NULL,
    person_users_user_id   INTEGER NOT NULL
);

ALTER TABLE settings ADD CONSTRAINT settings_pk PRIMARY KEY ( person_users_user_id );

CREATE TABLE task (
    task_id        INTEGER NOT NULL,
    name           VARCHAR(50) NOT NULL,
    info           VARCHAR(255),
    date_finish    DATE,
    list_list_id   INTEGER NOT NULL
);

ALTER TABLE task ADD CONSTRAINT task_pk PRIMARY KEY ( task_id );

CREATE TABLE team (
    team_id   INTEGER NOT NULL,
    name      VARCHAR(50) NOT NULL
);

ALTER TABLE team ADD CONSTRAINT team_pk PRIMARY KEY ( team_id );

CREATE TABLE users (
    user_id    INTEGER NOT NULL,
    login      VARCHAR(50) NOT NULL,
    password   VARCHAR(50) NOT NULL
);

ALTER TABLE users ADD CONSTRAINT users_pk PRIMARY KEY ( user_id );

ALTER TABLE list
    ADD CONSTRAINT list_team_fk FOREIGN KEY ( team_team_id )
        REFERENCES team ( team_id );

ALTER TABLE person
    ADD CONSTRAINT person_team_fk FOREIGN KEY ( team_team_id )
        REFERENCES team ( team_id );

ALTER TABLE person
    ADD CONSTRAINT person_users_fk FOREIGN KEY ( users_user_id )
        REFERENCES users ( user_id )
            ON DELETE CASCADE;

ALTER TABLE pomodoro
    ADD CONSTRAINT pomodoro_person_fk FOREIGN KEY ( person_user_id )
        REFERENCES person ( users_user_id );

ALTER TABLE settings
    ADD CONSTRAINT settings_person_fk FOREIGN KEY ( person_users_user_id )
        REFERENCES person ( users_user_id )
            ON DELETE CASCADE;

ALTER TABLE task
    ADD CONSTRAINT task_list_fk FOREIGN KEY ( list_list_id )
        REFERENCES list ( list_id )
            ON DELETE CASCADE;