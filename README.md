# Sistema de Registro de Estudantes

Este é um Sistema desenvolvido em C que permite gerenciar um registro de estudantes. Ele utiliza a biblioteca gráfica GTK+ 3 para fornecer uma interface de usuário intuitiva e amigável. O sistema segue os princípios do Domain-Driven Design (DDD) e é organizado em módulos, tornando o código mais fácil de manter e entender.

## Características

- **Interface Gráfica:** O sistema utiliza a biblioteca GTK+ 3 para criar uma interface gráfica intuitiva e fácil de usar. A interface inclui formulários para adicionar e editar estudantes, uma lista para visualizar todos os estudantes e uma função de pesquisa para encontrar estudantes pelo CPF.

- **Registro de Estudantes:** O sistema permite adicionar, editar, visualizar e remover estudantes. Os detalhes do estudante incluem o nome completo, CPF, curso, ano de matrícula e notas.

- **Pesquisa de Estudantes:** O sistema inclui uma função de pesquisa que permite encontrar estudantes pelo CPF.

- **Armazenamento de Dados:** Os dados dos estudantes são armazenados em um arquivo `students.txt`, permitindo que os dados persistam entre as execuções do sistema.

## Estrutura do Projeto

O projeto é baseado em módulos e utiliza os conceitos de Domain-Driven Design (DDD). A estrutura do projeto é dividida nas seguintes pastas:

- **infra:** Contém o código para a infraestrutura de suporte que o sistema utiliza, como a interface gráfica e o armazenamento de dados.

- **module/student/entities:** Contém as entidades do domínio do sistema, que são os objetos do mundo real que o sistema gerencia.

- **module/student/useCases:** Contém o código para os casos de uso do sistema, que são as operações específicas que o sistema pode realizar.

- **module/student/presentation:** Contém o código para a interface do usuário do sistema, que é como o sistema interage com o usuário.

- **shared:** Contém código que é compartilhado entre diferentes partes do sistema. Isso pode incluir funções utilitárias, definições de tipos e constantes.

## Compilação e Execução

Para compilar o sistema, você precisa ter o compilador GCC e a biblioteca GTK+ 3 instalados no seu sistema. Você pode compilar o sistema usando o arquivo `CMakeLists.txt` incluído.

Para executar o sistema, você pode executar o arquivo executável gerado pela compilação.
