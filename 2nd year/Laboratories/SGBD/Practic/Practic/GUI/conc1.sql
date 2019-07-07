begin tran;
    update Supe set mod_de_preparare = 'dirty' where cod_bucatar = 1;
    waitfor delay '00:00:10';
rollback tran;
