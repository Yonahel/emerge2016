import requests
import vdp_utils
import json
import serial

ser = serial.Serial('/dev/ttyACM0' , 9600)   #Use tty.usbmodem1421 on mac, and the appropriate com port on windows

info = '''{
    "acquirerCountryCode": "840",
    "acquiringBin": "408999",
    "amount": "124.02",
    "businessApplicationId": "AA",
    "cardAcceptor": {
        "address": {
            "country": "USA",
            "county": "San Mateo",
            "state": "CA",
            "zipCode": "94404"
        },
    "idCode": "ABCD1234ABCD123",
    "name": "Visa Inc. USA-Foster City",
    "terminalId": "ABCD1234"
    },
    "cavv": "0700100038238906000013405823891061668252",
    "foreignExchangeFeeTransaction": "11.99",
    "localTransactionDateTime": "2016-04-17T06:23:14",
    "retrievalReferenceNumber": "330000550000",
    "senderCardExpiryDate": "2015-10",
    "senderCurrencyCode": "USD",
    "senderPrimaryAccountNumber": "4895142232120006",
    "surcharge": "11.99",
    "systemsTraceAuditNumber": "451001"
}'''

user_id = 'Q07TTM1QXB84ETDK2BME215LadbnrK1ifTQkNmCnnZKZPWAqw'
password = 'DkZrzD2PCY6MdCM32xNF2Ox'
base_uri = 'visadirect/'
resource_path = 'fundstransfer/v1/pullfundstransactions/'
url = 'https://sandbox.api.visa.com/' + base_uri + resource_path
headers = {'content-type': 'application/json', 'accept':'application/json'}
BASE_URL = 'https://sandbox.api.visa.com'

# Make the call
r = requests.post(url,
  cert = ('cert.pem','privateKey.pem'),
  headers = headers,
  auth = (user_id, password),
  data = info)

# Print the response
print r.status_code
print r.content
def pullFunds(S):
    uri = '/visadirect/fundstransfer/v1/pullfundstransactions/'
    body = json.loads(info)
    r = S.post(BASE_URL + uri, json = body)
    print json.dumps(body, indent = 4)
    balance = body['amount']
    ser.write(str(balance))
    print 'Final balance:', balance
    return r


def main():
    user_id = 'Q07TTM1QXB84ETDK2BME215LadbnrK1ifTQkNmCnnZKZPWAqw'
    password = 'DkZrzD2PCY6MdCM32xNF2Ox'
    cert = 'cert.pem'
    key = 'privateKey.pem'

    with vdp_utils.MSession(user_id, password, cert, key) as S:
        S.headers.update({'content-type': 'application/json',
                         'accept': 'application/json'})
        r = pullFunds(S)

    print r.status_code
    print r.content


if __name__ == '__main__':
    main()
