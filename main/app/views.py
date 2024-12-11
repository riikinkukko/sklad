from django.shortcuts import render
from django.http import HttpResponseRedirect
from django.views.decorators.csrf import csrf_exempt
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from .models import Item_s


data_list = []


def index(request):
    global data_list
    if request.method == 'POST':
        data_list = []
        order_A3 = request.POST.get('А3col')
        order_B2 = request.POST.get('Б2col')
        if order_A3 == '':
            order_A3 = '0'
        if order_B2 == '':
            order_B2 = '0'
        print(order_A3, order_B2)
        data_list = [order_A3, order_B2]
        return HttpResponseRedirect('/')

    items = Item_s.objects.filter(availability=True)
    return render(request, 'app/index.html', {
        'items': items,
    })


class DataListView(APIView):
    @csrf_exempt
    def get(self, request):
        global data_list
        data_to_send = data_list[:]
        data_list = []
        return Response(data_to_send, status=status.HTTP_200_OK)

