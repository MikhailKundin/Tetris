PGDMP     (                	    x            Tetris    12.1    12.1 	               0    0    ENCODING    ENCODING        SET client_encoding = 'UTF8';
                      false                       0    0 
   STDSTRINGS 
   STDSTRINGS     (   SET standard_conforming_strings = 'on';
                      false                       0    0 
   SEARCHPATH 
   SEARCHPATH     8   SELECT pg_catalog.set_config('search_path', '', false);
                      false                       1262    24576    Tetris    DATABASE     �   CREATE DATABASE "Tetris" WITH TEMPLATE = template0 ENCODING = 'UTF8' LC_COLLATE = 'Russian_Russia.1251' LC_CTYPE = 'Russian_Russia.1251';
    DROP DATABASE "Tetris";
                postgres    false            �            1259    24577    RecordTable    TABLE     �   CREATE TABLE public."RecordTable" (
    "Date" timestamp without time zone NOT NULL,
    "Name" character(10),
    "Id" integer NOT NULL,
    "Points" integer NOT NULL
);
 !   DROP TABLE public."RecordTable";
       public         heap    postgres    false                      0    24577    RecordTable 
   TABLE DATA           G   COPY public."RecordTable" ("Date", "Name", "Id", "Points") FROM stdin;
    public          postgres    false    202   *	       �
           2606    24581    RecordTable RecordTable_pkey 
   CONSTRAINT     `   ALTER TABLE ONLY public."RecordTable"
    ADD CONSTRAINT "RecordTable_pkey" PRIMARY KEY ("Id");
 J   ALTER TABLE ONLY public."RecordTable" DROP CONSTRAINT "RecordTable_pkey";
       public            postgres    false    202            �
           2620    32775    RecordTable DateTr    TRIGGER     s   CREATE TRIGGER "DateTr" BEFORE INSERT ON public."RecordTable" FOR EACH ROW EXECUTE FUNCTION public."DateTrFunc"();
 /   DROP TRIGGER "DateTr" ON public."RecordTable";
       public          postgres    false    202            �
           2620    32772    RecordTable IdTr    TRIGGER     o   CREATE TRIGGER "IdTr" BEFORE INSERT ON public."RecordTable" FOR EACH ROW EXECUTE FUNCTION public."IdTrFunc"();
 -   DROP TRIGGER "IdTr" ON public."RecordTable";
       public          postgres    false    202               �   x����
�@����S���f�u=]�"
<uY�rA4�>�u���×�a�2����T'�d6`�m�[�@,��?��8��Ѵwu���؏�m���A�_�w�-X�����Ge�b�Ѹ�F�l��.��6ڇϫl�Y'�^}k�nmk��~����n�S
2���ק����*�P���Z�     