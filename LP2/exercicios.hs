import Data.Array
import System.IO
import Data.Char

qtdIguais a b c | (a == b) && (a == c) = 3
				| (a == b) || (a == c) || (b == c) = 2
				| otherwise = 0

media3 a b c = (a+b+c)/3

qtdMaiorMedia a b c | (a > media3 a b c) && (b > media3 a b c) || (a > media3 a b c) && (c > media3 a b c) || (c > media3 a b c) && (b > media3 a b c) = 2
					| otherwise = 1
					
quadrado x = x*x

potencia4 x = (quadrado x) * (quadrado x)

maiuscula :: Char->Char
maiuscula a = chr(ord(a)-32)

minuscula :: Char->Char
minuscula a = chr(ord(a)+32)

lerInt :: IO Int
lerInt = readLn

soma :: IO ()
soma = do 
			print("Digite o primeiro numero: ")
			a <- lerInt
			print("Digite o segundo numero: ")
			b <- lerInt
			print("A soma e:")
			print(a+b)


inverte [] = []
inverte (a:x) = inverte x ++ (a:[])

desenhar::[Char] -> IO ()
desenhar (a:x) | a == '1' = do 
							print("<3 ") 
							desenhar x
				| a == '0' = do
							print("=D ")
							desenhar x
				| otherwise = do
								print("D=") 
								desenhar x

pegarArquivo :: IO ()
pegarArquivo = do
				arq <- openFile "teste.txt" ReadMode
				conteudo <- hGetContents arq
				desenhar conteudo
				hClose arq