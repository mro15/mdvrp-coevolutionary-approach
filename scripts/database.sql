CREATE TABLE experiments (
    id INTEGER,
    seed INTEGER,
    nIndividuals INTEGER,
    mutationRatio DOUBLE PRECISION,
    iterations INTEGER,
    duration INTEGER,
    constCapacity INTEGER,
    constDuration INTEGER,
    nRoutes INTEGER,
    nDepots INTEGER,
    assignment TEXT,
    mutOp TEXT,
    crOp TEXT,
    selOp TEXT,
    instance TEXT,
    routes TEXT,
    graph TEXT
);
